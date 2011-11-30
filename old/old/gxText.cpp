#include "gxText.h"

Text::Text(GenericInstance *instance, Pointer::RetainAction action)
	:Displayable(instance, action) {
}
Text::Text(GenericInstance *instance, const Interface &interface, Pointer::RetainAction action)
	:Displayable(instance, interface, action) {
}
void Text::asText(Text &result) {
	result= *this;
}
/** 
	@todo Implement
*/
void Text::asTextOfWidth(const Integer &width, const Character &padding, Text &result) {
}
/** 
	@todo Implement
*/
void Text::getCharacter(const Integer &index, Character &result) {
}
