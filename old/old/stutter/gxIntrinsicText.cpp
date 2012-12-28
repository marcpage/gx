#include "gxIntrinsicText.h"

namespace gx {

	IntrinsicText::IntrinsicText(const Type &actualType)
		:Intrinsic(actualType) {
	}
	uint32_t IntrinsicText::length() const {
		return 0;
	}
	uint32_t IntrinsicText::character(uint32_t index) const {
		return 0;
	}
	bool IntrinsicText::equals(const Text &other) const {
		return false;
	}
	IntrinsicText::~IntrinsicText() {
	}

} // namespace gx
