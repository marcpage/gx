#ifndef __ASCIIText_h__
#define __ASCIIText_h__

#include "gxText.h"

class ASCIIText : public Text {
	public:
		enum Members {
			Storage,
			kCountOfMembers
		};
		enum Constants {
			kCountOfConstants
		};
		static const Type		type;
		static const Interface	interface;
		static void init();
		ASCIIText(const char *cString);
		ASCIIText(const void *buffer, size_t size);
		ASCIIText(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~ASCIIText() {}
		virtual void asText(Text &result);
		virtual void asTextOfWidth(const Integer &width, const Character &padding, Text &result);
		virtual void getCharacter(const Integer &index, Character &result);
};

#endif // __Text_h__
