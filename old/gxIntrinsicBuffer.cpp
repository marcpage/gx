#include "gxIntrinsicBuffer.h"
#include "gxBuffer.h"

IntrinsicBuffer::IntrinsicBuffer(size_t amount)
	:Intrinsic(Buffer::type), _value(amount, '\0') {
}
IntrinsicBuffer::IntrinsicBuffer(const void *data, size_t amount)
	:Intrinsic(Buffer::type), _value(reinterpret_cast<const char*>(data), amount) {
}
IntrinsicBuffer::IntrinsicBuffer(const std::string &data)
	:Intrinsic(Buffer::type), _value(data) {
}
/** 
	@todo implement
*/
const void *IntrinsicBuffer::value() const {
}
/** 
	@todo implement
*/
const size_t IntrinsicBuffer::size() const {
}
/** 
	@todo implement
*/
GenericInstance *IntrinsicBuffer::clone() {
}
