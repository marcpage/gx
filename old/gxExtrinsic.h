#ifndef __gxExtrinsic_h__
#define __gxExtrinsic_h__

#include "gxInstance.h"

namespace gx {

	class Extrinsic : public Instance {
		public:
			Instance(const Type &actualType);
		protected:
			virtual ~Instance();
	};

} // namespace gx

#endif // __gxExtrinsic_h__
