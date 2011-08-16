#include "gxNamedType.h"
#include "gxType.h"
#include "gxInterface.h"

const Type NamedType::type;
const Interface NamedType::interface;

void NamedType::init() {
}
NamedType::NamedType(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
