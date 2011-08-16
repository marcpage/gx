#ifndef __IntrinsicDisplayable_h__
#define __IntrinsicDisplayable_h__

#include "gxInstrinsic.h"

class IntrinsicDisplayable : public Intrinsic {
	public:
		IntrinsicDisplayable();
		virtual void asText(Text &result)= 0;
		virtual void asTextOfWidth(const Integer &width, const Character &padding, Text &result)= 0;
	protected:
		virtual ~IntrinsicDisplayable() {}
};

#endif // __IntrinsicDisplayable_h__
