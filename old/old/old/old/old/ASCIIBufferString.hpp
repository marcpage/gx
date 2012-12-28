#include "AllocatedBuffer.h"

inline StringPtr ASCIIBufferString::create(BufferParam asciiBuffer) {
	return StringPtr(new ASCIIBufferString(asciiBuffer));
}
/** 
	Passing NULL to AllocatedBuffer::create tells it to allocate a buffer but not copy anything.
	Since we just created it, we are the only ones referencing it and can violate constness.
*/
inline ASCIIBufferStringPtr ASCIIBufferString::serialize(StringParam string) {
	const size_t		size= string->length();
	AllocatedBufferPtr	buffer(AllocatedBuffer::create(NULL, size));
	Buffer::Byte		*raw= const_cast<Buffer::Byte*>(buffer->data());
	
	for(size_t index= 0; index < size; ++index) {
		uint32_t	character= string->at(index);
		
		AssertMessageException(character < 128);
		raw[index]= static_cast<Buffer::Byte>(character);
	}
	return ASCIIBufferStringPtr(new ASCIIBufferString(BufferPtr(&*buffer)));
}
inline uint32_t ASCIIBufferString::at(size_t index) const {
	return static_cast<uint32_t>((*_buffer)[index]);
}
inline std::string &ASCIIBufferString::convert(std::string &buffer) {
	const size_t	bytes= _buffer->length();
	
	buffer.assign(bytes, '\0');
	for(size_t index= 0; index < _buffer->length(); ++index) {
		const_cast<char*>(buffer.data())[index]= (*_buffer)[index];
	}
	return buffer;
}
inline size_t ASCIIBufferString::length() const {
	return _buffer->length();
}
inline size_t ASCIIBufferString::parts() const {
	return 1;
}
inline ASCIIBufferString::ASCIIBufferString(BufferParam asciiBuffer)
	:_buffer(asciiBuffer) {
}
inline ASCIIBufferString::~ASCIIBufferString() {
}
