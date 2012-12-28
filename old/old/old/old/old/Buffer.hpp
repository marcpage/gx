inline Buffer::Buffer() {
}
inline Buffer::~Buffer() {
}
inline BufferPtr operator+(BufferParam b1, BufferParam b2) {
	return b1->add(b2);
}
