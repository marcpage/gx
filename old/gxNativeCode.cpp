#include "gxNativeCode.h"
#include "gxType.h"
#include "gxInterface.h"

const Type NativeCode::type;
const Interface NativeCode::interface;

void NativeCode::init() {
}
NativeCode::NativeCode(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
