#include "gxIntrinsicASCIIText.h"

namespace gx {

	IntrinsicASCIIText::IntrinsicASCIIText(const Type &actualType, const void *buffer, size_t length, Dispose action)
		:IntrinsicText(actualType), _buffer(buffer), _length(length), _action(action) {
		if(_length < 0) {
			_length= strlen(reinterpret_cast<const char*>(_buffer));
		}
	}
	uint32_t IntrinsicASCIIText::length() const {
		return _length;
	}
	/**
		@todo assert within bounds
	*/
	uint32_t IntrinsicASCIIText::character(uint32_t index) const {
		return static_cast<uint32_t>(reinterpret_cast<const uint8_t*>(_buffer)[index]);
	}
	IntrinsicASCIIText::~IntrinsicASCIIText() {
		if(_action) {
			_action(_buffer);
		}
	}

} // namespace gx
