#include "gxInstance.h"

namespace gx {

	Instance::Instance(const Type &actualType)
		:_type(actualType) {
	}
	bool Instance::is(const Type &actualType) {
		ThrowMessageException("TODO: implement");
	}
	bool Instance::does(const Interface &interface) {
		ThrowMessageException("TODO: implement");
	}
	template<class T> T* Instance::modifiableCopy() {
		ThrowMessageException("TODO: implement");
	}
	const Type &Instance::type() const {
		return _type;
	}
	Instance::~Instance() {
	}
	Instance *Instance::clone() {
		ThrowMessageException("TODO: implement");
	}

} // namespace gx
