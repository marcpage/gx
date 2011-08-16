#include "gxDisplayable.h"

Displayable::Displayable(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, action) {
}
Displayable::Displayable(GenericInstance *instance, const Interface &interface, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
