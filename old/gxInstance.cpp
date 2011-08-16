#include "gxInstance.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Instance::type;
const Interface Instance::interface;

void Instance::init() {
}
Instance::Instance(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
