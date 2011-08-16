#ifndef __IntrinsicReference_h__
#define __IntrinsicReference_h__

#include "gxIntrinsic.h"

class IntrinsicReference : public Intrinsic {
	public:
		IntrinsicReference();
	protected:
		virtual ~IntrinsicReference();
	private:
		Pointer	_value;
};

#endif // __IntrinsicReference_h__
