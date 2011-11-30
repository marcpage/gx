#ifndef __Interface_h__
#define __Interface_h__

#include "gxPointer.h"

class Interface : public Pointer {
	public:
		enum Members {
			Name,
			Parent,
			Methods,
			kCountOfMembers
		};
		enum Constants {
			AllInterfaces,
			kCountOfConstants
		};
		static const Type		type;
		static const Interface	interface;
		static void init();
		Interface(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Interface() {}
};

#endif // __Interface_h__
