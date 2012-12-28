#include "gxInterface.h"
#include "gxType.h"

const Type Interface::type;
const Interface Interface::interface;

void Interface::init() {
}
Interface::Interface(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
