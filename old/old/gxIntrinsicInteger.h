#ifndef __IntrinsicInteger_h__
#define __IntrinsicInteger_h__

#include "gxIntrinsicNumber.h"

class IntrinsicInteger : public IntrinsicNumber {
	public:
		IntrinsicInteger();
		virtual void asTextOfRadix(const Integer &width, const Character &padding, const Integer &radix, Text &result)= 0;
		virtual void shiftLeft(const Integer &amount, Integer &result)= 0;
		virtual void shiftRight(const Integer &amount, Integer &result)= 0;
		virtual void isOdd(Boolean &result)= 0;
		virtual void isEven(Boolean &result)= 0;
		virtual void highestSetBit(Integer &result)= 0;
		virtual void lowestSetBit(Integer &result)= 0;
		virtual void lowestClearedBit(Integer &result)= 0;
		virtual void andWith(const Integer &other, Integer &result)= 0;
		virtual void orWith(const Integer &other, Integer &result)= 0;
		virtual void exclusiveOrWith(const Integer &other, Integer &result)= 0;
		virtual void invertBits(Integer &result)= 0;
	protected:
		virtual ~IntrinsicInteger() {}
};

#endif // __NumberGenericInstance_h__
