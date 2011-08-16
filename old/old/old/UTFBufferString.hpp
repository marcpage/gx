inline String::Ptr UTFBufferString::create(BufferParam utfBuffer, Endian endian) {
		AssertMessageException(utfBuffer->length() % sizeof(uint32_t) == 0);
	return Ptr(new UTFBufferString(utfBuffer));
}
/** 
	Passing NULL to AllocatedBuffer::create tells it to allocate a buffer but not copy anything.
	Since we just created it, we are the only ones referencing it and can violate constness.
*/
inline UTFBufferStringPtr UTFBufferString::serialize(const Ptr &string) {
	const size_t	size= string.length();
	BufferPtr		buffer(AllocatedBuffer::create(NULL, size));
	Buffer::Byte	*raw= const_cast<Buffer::Byte*>(buffer->data());
	
	for(size_t index= 0; index < size; ++index) {
		uint32_t	character= string->at(index);
		
		AssertMessageException(character < 128);
		raw[index]= static_cast<Buffer::Byte>(character);
	}
	return Ptr(new UTFBufferString(buffer));
}
inline uint32_t UTFBufferString::at(size_t index) const {
	uint32_t			value= 0;
	const Buffer::Byte	bytes[]= {
		(*_buffer)[index * sizeof(uint32_t) + 0],
		(*_buffer)[index * sizeof(uint32_t) + 1],
		(*_buffer)[index * sizeof(uint32_t) + 2],
		(*_buffer)[index * sizeof(uint32_t) + 3]
	};
	const 				byteCount= sizeof(bytes)/sizeof(bytes[0]);
	
	switch(_endian) {
		case BigEndian:
			for(int index= 0; index < byteCount; ++ index) {
				value= (value << 8) | bytes[index];
			}
			break;
		case LittleEndian:
			for(int index= 0; index < byteCount; ++ index) {
				value= (value << 8) | bytes[byteCount - index - 1];
			}
			break;
		case NativeEndian:
			value= *reinterpret_cast<uint32_t*>(bytes);
			break;
	}
	return value;
}
inline std::wstring &UTFBufferString::convert(std::wstring &buffer) {
	const size_t	bytes= _buffer->length();
	
	buffer.assign(bytes, '\0');
	for(size_t index= 0; index < _buffer->length(); ++index) {
		const_cast<wchar_t*>(buffer->data())[index]= static_cast<wchar_t>(at(index));
	}
	return buffer;
}
inline size_t UTFBufferString::length() const {
	return _buffer->length() / sizeof(uint32_t);
}
inline size_t UTFBufferString::parts() const {
	return 1;
}
inline UTFBufferString::UTFBufferString(BufferParam utfBuffer, Endian endian)
	:_buffer(asciiBuffer), _endian(endian) {
}
inline UTFBufferString::~UTFBufferString() {
}
