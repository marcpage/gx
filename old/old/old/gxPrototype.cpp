#include "gxPrototype.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Prototype::type;
const Interface Prototype::interface;

void Prototype::init() {
}
Prototype::Prototype(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}

