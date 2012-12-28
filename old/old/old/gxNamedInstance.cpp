#include "gxNamedInstance.h"
#include "gxType.h"
#include "gxInterface.h"

const Type NamedInstance::type;
const Interface NamedInstance::interface;

void NamedInstance::init() {
}
NamedInstance::NamedInstance(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
