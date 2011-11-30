#include "gxInterface.h"
#include "gxInstance.h"

namespace gx {

	Interface::Interface()
		:Pointer(NULL, Pointer::DoNotRetain) {
	}
	Interface::Interface(Instance *instance, Pointer::RetainAction action)
		:Pointer(instance, action) {
	}
	Interface::~Interface() {
	}

} // namespace gx
