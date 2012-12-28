#ifndef __Displayable_h__
#define __Displayable_h__

#include "gxPointer.h"

class Displayable : public Pointer {
	public:
		Displayable(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		Displayable(GenericInstance *instance, const Interface &interface, Pointer::RetainAction action= Retain);
		~Displayable() {}
		virtual void asText(Text &result)= 0;
		virtual void asTextOfWidth(const Integer &width, const Character &padding, Text &result)= 0;
};

#endif // __Displayable_h__
