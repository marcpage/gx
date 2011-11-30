#include "gxIntrinsicFloat.h"
#include <cstdio>

IntrinsicFloat(Float instanceValue)
	:_value(instanceValue) {
}
Float value() const {
	return _value;
}
void asText(Text &result) {
	char	buffer[256];
	int		size;
	
	size= snprintf(buffer, sizeof(buffer), "%f", _value);
	result= ASCIIText(buffer);
}
void asTextOfWidth(const Integer &width, const Character &padding, Text &result) {
}
void asTextOfFormat(const Integer &width, const Character &padding, const Integer &precision, Text &result) {
}
void addTo(const Number &amount, Number &result) {
}
void subtract(const Number &amount, Number &result) {
}
void multiplyBy(const Number &by, Number &result) {
}
void divideBy(const Number &denominator, Number &quotient) {
}
void remainderOf(const Number &denominator, Number &remainder) {
}
void inverse(Number &result) {
}
void magnitude(Number &result) {
}
void squared(Number &result) {
}
void cubed(Number &result) {
}
void raisedTo(const Number &power, Number &result) {
}
void tenRaisedTo(Number &result) {
}
void twoRaisedTo(Number &result) {
}
void eRaisedTo(Number &result) {
}
void squareRoot(Number &result) {
}
void cubeRoot(Number &result) {
}
void root(const Number &root, Number &result) {
}
void negate(Number &result) {
}
void logarithm(const Number &base, Number &result) {
}
void naturalLogarithm(Number &result) {
}
void baseTwoLogarithm(Number &result) {
}
void baseTenLogarithm(Number &result) {
}
void isNegative(Boolean &result) {
}
void isLessThan(const Number &value, Boolean &result) {
}
void isGreaterThan(const Number &value, Boolean &result) {
}
void equals(const Number &value, Boolean &result) {
}
void near(const Number &value, Boolean &result) {
}
void within(const Number &delta, const Number &value, Boolean &result) {
}
void isLessThanOrEqualTo(const Number &value, Boolean &result) {
}
void isGreaterThanOrEqualTo(const Number &value, Boolean &result) {
}
void sine(Number &result) {
}
void cosine(Number &result) {
}
void tangent(Number &result) {
}
void cotangent(Number &result) {
}
void secant(Number &result) {
}
void cosecant(Number &result) {
}
void arcSine(Number &result) {
}
void arcCosine(Number &result) {
}
void arcTangent(Number &result) {
}
void arcCotangent(Number &result) {
}
void arcSecant(Number &result) {
}
void arcCosecant(Number &result) {
}
void angle(const Number &y, Number &result) {
} ///< this(x), y is a vector of an angle result in radians
void hyperbolicSine(Number &result) {
}
void hyperbolicCosine(Number &result) {
}
void hyperbolicTangent(Number &result) {
}
void hyperbolicCotangent(Number &result) {
}
void hyperbolicSecant(Number &result) {
}
void hyperbolicCosecant(Number &result) {
}
void hyperbolicArcSine(Number &result) {
}
void hyperbolicArcCosine(Number &result) {
}
void hyperbolicArcTangent(Number &result) {
}
void hyperbolicArcCotangent(Number &result) {
}
void hyperbolicArcSecant(Number &result) {
}
void hyperbolicArcCosecant(Number &result) {
}
void nearestInteger(Integer &result) {
}
void integerNearestNegativeInfinity(Integer &result) {
}
void integerNearestInfinity(Integer &result) {
}
void wholeNumber(Integer &result) {
}
void fractionalNumber(Number &result) {
}
void real(Number &result) {
}
void imaginary(Number &result) {
}
GenericInstance *clone() {
}
