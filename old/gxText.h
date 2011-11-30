#ifndef __gxText_h__
#define __gxText_h__

#include "gxPointer.h"

namespace gx {

	class Text : public Pointer {
		public:
			static void populateInterface(Interface &interface);
			Text();
			Text(Instance *instance, Pointer::RetainAction action);
			uint32_t length() const;
			uint32_t character(uint32_t index) const;
			bool equals(const Text &other) const;
			~Text();
	};

} // namespace gx

#endif // __gxText_h__
