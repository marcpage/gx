#include "gxFloat.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Float::type;
const Interface Float::interface;

void Float::init() {
}
Float::Float(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
