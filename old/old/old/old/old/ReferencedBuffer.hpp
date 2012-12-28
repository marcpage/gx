inline BufferPtr ReferencedBuffer::create(const void *buffer, size_t theLength) {
	return BufferPtr(new ReferencedBuffer(buffer, theLength));
}
inline const ReferencedBuffer::Byte &ReferencedBuffer::operator[](size_t index) const {
	AssertMessageException( (index < _length) );
	return _buffer[index];
}
inline size_t ReferencedBuffer::length() const {
	return _length;
}
inline uint32_t ReferencedBuffer::parts() const {
	return 1;
}
inline ReferencedBuffer::ReferencedBuffer(const void *buffer, size_t bufferLength)
	:_buffer(reinterpret_cast<const unsigned char*>(buffer)), _length(bufferLength) {
}
inline ReferencedBuffer::~ReferencedBuffer() {
}
