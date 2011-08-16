#include "gxDispatch.h"
#include "gxType.h"
#include "gxInterface.h"

const Type Dispatch::type;
const Interface Dispatch::interface;

void Dispatch::init() {
}
Dispatch::Dispatch(Interface useInterface) {
}
Dispatch::Dispatch(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
