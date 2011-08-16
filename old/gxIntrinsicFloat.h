#ifndef __IntrinsicFloat_h__
#define __IntrinsicFloat_h__

#include "gxIntrinsicNumber.h"

class IntrinsicFloat : public IntrinsicNumber {
	public:
		/** IEEE 754 double precision 64-bit floating point, 52-bit (effectively 53-bit) fraction, 11-bit exponent, 1-bit sign
			Maximum value for the fraction: 9007199254740990 (4503599627370495 with implied 1)
		*/
		typedef double	Float;
		IntrinsicFloat(Float instanceValue);
		Float value() const;
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
	protected:	
		virtual ~IntrinsicFloat() {}
		virtual GenericInstance *clone();
	private:
		Float	_value;
};

#endif // __IntrinsicFloat_h__
