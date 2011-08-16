#ifndef __gxIntrinsic_h__
#define __gxIntrinsic_h__

#include "gxInstance.h"

namespace gx {

	class Intrinsic : public Instance {
		public:
			Intrinsic(const Type &actualType);
		protected:
			virtual ~Intrinsic();
	};

} // namespace gx

#endif // __gxIntrinsic_h__
