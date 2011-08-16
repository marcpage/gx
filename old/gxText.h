#ifndef __Text_h__
#define __Text_h__

#include "gxDisplayable.h"

class Text : public Displayable {
	public:
		Text(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		Text(GenericInstance *instance, const Interface &interface, Pointer::RetainAction action= Retain);
		~Text() {}
		virtual void asText(Text &result);
		virtual void asTextOfWidth(const Integer &width, const Character &padding, Text &result);
		virtual void getCharacter(const Integer &index, Character &result);
};

#endif // __Text_h__
