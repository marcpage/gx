#ifndef __Intrinsic_h__
#define __Intrinsic_h__

#include "gxGenericInstance.h"

class Intrinsic : public GenericInstance {
	public:
		Intrinsic(const Type &actualType);
	protected:
		virtual ~Intrinsic() {}
};

#endif // __Intrinsic_h__
