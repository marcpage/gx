#include "gxPrototype.h"

namespace gx {

	Prototype::Prototype()
		:Pointer(NULL, Pointer::DoNotRetain) {
	}
	Prototype::Prototype(Instance *instance, Pointer::RetainAction action)
		:Pointer(instance, action) {
	}
	Prototype::~Prototype() {
	}

} // namespace gx
