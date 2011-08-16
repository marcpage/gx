#include "gxASCIIText.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxExtrinsic.h"
#include "gxBuffer.h"

const Type ASCIIText::type;
const Interface ASCIIText::interface;

void ASCIIText::init() {
}

ASCIIText::ASCIIText(const char *cString)
	:Text(new Extrinsic(type, kCountOfMembers), interface, Pointer::DoNotRetain) {
	ref<Extrinsic>()[Storage]= Buffer(cString, strlen(cString));
}
ASCIIText::ASCIIText(const void *buffer, size_t size)
	:Text(new Extrinsic(type, kCountOfMembers), interface, Pointer::DoNotRetain) {
	ref<Extrinsic>()[Storage]= Buffer(buffer, size);
}
/** 
	@todo check instance to make sure it supports ASCIIText
*/
ASCIIText::ASCIIText(GenericInstance *instance, Pointer::RetainAction action)
	:Text(instance, interface, action) {
}
void ASCIIText::asText(Text &result) {
	result= *this;
}
/** 
	@todo Implement
*/
void ASCIIText::asTextOfWidth(const Integer &width, const Character &padding, Text &result) {
}
/** 
	@todo Implement
*/
void ASCIIText::getCharacter(const Integer &index, Character &result) {
}
