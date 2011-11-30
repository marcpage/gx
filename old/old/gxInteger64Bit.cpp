#include "gxInteger64Bit.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Integer64Bit::type;
const Interface Integer64Bit::interface;

/**
	@todo implement all the methods
*/
void Integer64Bit::init() {
}
Integer64Bit::Integer64Bit(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
