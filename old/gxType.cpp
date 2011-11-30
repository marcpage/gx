#include "gxType.h"

namespace gx {

	Type::Type()
		:Pointer(NULL, Pointer::DoNotRetain) {
	}
	Type::Type(Instance *instance, Pointer::RetainAction action)
		:Pointer(instance, action) {
	}
	Type::~Type() {
	}
} // namespace gx

