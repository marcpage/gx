#ifndef __IntrinsicNumber_h__
#define __IntrinsicNumber_h__

#include "gxIntrinsicDisplayable.h"

class IntrinsicNumber : public IntrinsicDisplayable {
	public:
		IntrinsicNumber();
		virtual void asTextOfFormat(const Integer &width, const Character &padding, const Integer &precision, Text &result)= 0;
		virtual void addTo(const Number &amount, Number &result)= 0;
		virtual void subtract(const Number &amount, Number &result)= 0;
		virtual void multiplyBy(const Number &by, Number &result)= 0;
		virtual void divideBy(const Number &denominator, Number &quotient)= 0;
		virtual void remainderOf(const Number &denominator, Number &remainder)= 0;
		virtual void inverse(Number &result)= 0;
		virtual void magnitude(Number &result)= 0;
		virtual void squared(Number &result)= 0;
		virtual void cubed(Number &result)= 0;
		virtual void raisedTo(const Number &power, Number &result)= 0;
		virtual void tenRaisedTo(Number &result)= 0;
		virtual void twoRaisedTo(Number &result)= 0;
		virtual void eRaisedTo(Number &result)= 0;
		virtual void squareRoot(Number &result)= 0;
		virtual void cubeRoot(Number &result)= 0;
		virtual void root(const Number &root, Number &result)= 0;
		virtual void negate(Number &result)= 0;
		virtual void logarithm(const Number &base, Number &result)= 0;
		virtual void naturalLogarithm(Number &result)= 0;
		virtual void baseTwoLogarithm(Number &result)= 0;
		virtual void baseTenLogarithm(Number &result)= 0;
		virtual void isNegative(Boolean &result)= 0;
		virtual void isLessThan(const Number &value, Boolean &result)= 0;
		virtual void isGreaterThan(const Number &value, Boolean &result)= 0;
		virtual void equals(const Number &value, Boolean &result)= 0;
		virtual void near(const Number &value, Boolean &result)= 0;
		virtual void within(const Number &delta, const Number &value, Boolean &result)= 0;
		virtual void isLessThanOrEqualTo(const Number &value, Boolean &result)= 0;
		virtual void isGreaterThanOrEqualTo(const Number &value, Boolean &result)= 0;
		virtual void sine(Number &result)= 0;
		virtual void cosine(Number &result)= 0;
		virtual void tangent(Number &result)= 0;
		virtual void cotangent(Number &result)= 0;
		virtual void secant(Number &result)= 0;
		virtual void cosecant(Number &result)= 0;
		virtual void arcSine(Number &result)= 0;
		virtual void arcCosine(Number &result)= 0;
		virtual void arcTangent(Number &result)= 0;
		virtual void arcCotangent(Number &result)= 0;
		virtual void arcSecant(Number &result)= 0;
		virtual void arcCosecant(Number &result)= 0;
		virtual void angle(const Number &y, Number &result)= 0; ///< this(x), y is a vector of an angle result in radians
		virtual void hyperbolicSine(Number &result)= 0;
		virtual void hyperbolicCosine(Number &result)= 0;
		virtual void hyperbolicTangent(Number &result)= 0;
		virtual void hyperbolicCotangent(Number &result)= 0;
		virtual void hyperbolicSecant(Number &result)= 0;
		virtual void hyperbolicCosecant(Number &result)= 0;
		virtual void hyperbolicArcSine(Number &result)= 0;
		virtual void hyperbolicArcCosine(Number &result)= 0;
		virtual void hyperbolicArcTangent(Number &result)= 0;
		virtual void hyperbolicArcCotangent(Number &result)= 0;
		virtual void hyperbolicArcSecant(Number &result)= 0;
		virtual void hyperbolicArcCosecant(Number &result)= 0;
		virtual void nearestInteger(Integer &result)= 0;
		virtual void integerNearestNegativeInfinity(Integer &result)= 0;
		virtual void integerNearestInfinity(Integer &result)= 0;
		virtual void wholeNumber(Integer &result)= 0;
		virtual void fractionalNumber(Number &result)= 0;
		virtual void real(Number &result)= 0;
		virtual void imaginary(Number &result)= 0;
	protected:
		virtual ~IntrinsicNumber() {}
};

#endif // __IntrinsicNumber_h__
