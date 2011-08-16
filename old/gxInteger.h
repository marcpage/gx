#ifndef __Integer_h__
#define __Integer_h__

#include "gxNumber.h"

class Integer : public Number {
	public:
		Integer(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Integer() {}
		virtual void asText(Text &result);
		virtual void asTextOfWidth(const Integer &width, const Character &padding, Text &result);
		virtual void asTextOfFormat(const Integer &width, const Character &padding, const Integer &precision, Text &result);
		virtual void addTo(const Number &amount, Number &result);
		virtual void subtract(const Number &amount, Number &result);
		virtual void multiplyBy(const Number &by, Number &result);
		virtual void divideBy(const Number &denominator, Number &quotient);
		virtual void remainderOf(const Number &denominator, Number &remainder);
		virtual void inverse(Number &result);
		virtual void magnitude(Number &result);
		virtual void squared(Number &result);
		virtual void cubed(Number &result);
		virtual void raisedTo(const Number &power, Number &result);
		virtual void tenRaisedTo(Number &result);
		virtual void twoRaisedTo(Number &result);
		virtual void eRaisedTo(Number &result);
		virtual void squareRoot(Number &result);
		virtual void cubeRoot(Number &result);
		virtual void root(const Number &root, Number &result);
		virtual void negate(Number &result);
		virtual void logarithm(const Number &base, Number &result);
		virtual void naturalLogarithm(Number &result);
		virtual void baseTwoLogarithm(Number &result);
		virtual void baseTenLogarithm(Number &result);
		virtual void isNegative(Boolean &result);
		virtual void isLessThan(const Number &value, Boolean &result);
		virtual void isGreaterThan(const Number &value, Boolean &result);
		virtual void equals(const Number &value, Boolean &result);
		virtual void near(const Number &value, Boolean &result);
		virtual void within(const Number &delta, const Number &value, Boolean &result);
		virtual void isLessThanOrEqualTo(const Number &value, Boolean &result);
		virtual void isGreaterThanOrEqualTo(const Number &value, Boolean &result);
		virtual void sine(Number &result);
		virtual void cosine(Number &result);
		virtual void tangent(Number &result);
		virtual void cotangent(Number &result);
		virtual void secant(Number &result);
		virtual void cosecant(Number &result);
		virtual void arcSine(Number &result);
		virtual void arcCosine(Number &result);
		virtual void arcTangent(Number &result);
		virtual void arcCotangent(Number &result);
		virtual void arcSecant(Number &result);
		virtual void arcCosecant(Number &result);
		virtual void angle(const Number &y, Number &result); ///< this(x), y is a vector of an angle result in radians
		virtual void hyperbolicSine(Number &result);
		virtual void hyperbolicCosine(Number &result);
		virtual void hyperbolicTangent(Number &result);
		virtual void hyperbolicCotangent(Number &result);
		virtual void hyperbolicSecant(Number &result);
		virtual void hyperbolicCosecant(Number &result);
		virtual void hyperbolicArcSine(Number &result);
		virtual void hyperbolicArcCosine(Number &result);
		virtual void hyperbolicArcTangent(Number &result);
		virtual void hyperbolicArcCotangent(Number &result);
		virtual void hyperbolicArcSecant(Number &result);
		virtual void hyperbolicArcCosecant(Number &result);
		virtual void nearestInteger(Integer &result);
		virtual void integerNearestNegativeInfinity(Integer &result);
		virtual void integerNearestInfinity(Integer &result);
		virtual void wholeNumber(Integer &result);
		virtual void fractionalNumber(Number &result);
		virtual void real(Number &result);
		virtual void imaginary(Number &result);
		virtual void asTextOfRadix(const Integer &width, const Character &padding, const Integer &radix, Text &result);
		virtual void shiftLeft(const Integer &amount, Integer &result);
		virtual void shiftRight(const Integer &amount, Integer &result);
		virtual void isOdd(Boolean &result);
		virtual void isEven(Boolean &result);
		virtual void highestSetBit(Integer &result);
		virtual void lowestSetBit(Integer &result);
		virtual void lowestClearedBit(Integer &result);
		virtual void andWith(const Integer &other, Integer &result);
		virtual void orWith(const Integer &other, Integer &result);
		virtual void exclusiveOrWith(const Integer &other, Integer &result);
		virtual void invertBits(Integer &result);
};

#endif // __Integer_h__
