#include "gxMethod.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Method::type;
const Interface Method::interface;

void Method::init() {
}
Method::Method(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
