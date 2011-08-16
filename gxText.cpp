#include "gxText.h"

namespace gx {

	void Text::populateInterface(Interface &interface, const TypeSystem &typeLookup) {
		enum Strings {
			StringCount
		};
		enum Methods {
			mCharacter,
			mLength,
			mFind,
			mSubstring,
			mAppend,
			MethodCount
		};
		Text	strings[StringCount + MethodCount];
		IntrinsicPrototype	*prototypes[];
		
		//interface.ref<IntrinsicInterface>().add(
	}
	Text::Text()
		:Pointer(NULL, Pointer::DoNotRetain) {
	}
	Text::Text(Instance *instance, Pointer::RetainAction action)
		:Pointer(instance, action) {
	}
	uint32_t Text::length() const {
		ThrowMessageException("TODO: Implement");
		return 0;
	}
	uint32_t Text::character(uint32_t index) const {
		ThrowMessageException("TODO: Implement");
		return 0;
	}
	bool Text::equals(const Text &other) const {
		ThrowMessageException("TODO: Implement");
		return false;
	}
	Text::~Text() {
	}

} // namespace gx
