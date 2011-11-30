#include "gxBuffer.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxIntrinsicBuffer.h"
#include "gxBuffer.h"

const Type	Buffer::type;
const Interface Buffer::interface;

void Buffer::init() {
}

Buffer::Buffer(size_t bufferSize)
	:Pointer(new IntrinsicBuffer(bufferSize), interface, Pointer::DoNotRetain) {
}
Buffer::Buffer(const void *data, size_t bufferSize)
	:Pointer(new IntrinsicBuffer(data, bufferSize), interface, Pointer::DoNotRetain) {
}

Buffer::Buffer(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
const void *Buffer::value() const {
	return ref<IntrinsicBuffer>().value();
}
const size_t Buffer::size() const {
	return ref<IntrinsicBuffer>().size();
}
