#ifndef __gxIntrinsicText_h__
#define __gxIntrinsicText_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxText.h"
#include <vector>

namespace gx {

	class IntrinsicText : public Intrinsic {
		public:
			IntrinsicText(const Type &actualType);
			virtual uint32_t length() const;
			virtual uint32_t character(uint32_t index) const;
			virtual bool equals(const Text &other) const;
		protected:
			virtual ~IntrinsicText();
	};

} // namespace gx

#endif // __gxIntrinsicText_h__
