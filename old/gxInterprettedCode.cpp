#include "gxInterprettedCode.h"
#include "gxType.h"
#include "gxInterface.h"

const Type InterprettedCode::type;
const Interface InterprettedCode::interface;

void InterprettedCode::init() {
}
InterprettedCode::InterprettedCode(GenericInstance *instance, Pointer::RetainAction action)
	:Pointer(instance, interface, action) {
}
