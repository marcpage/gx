#ifndef __Method_h__
#define __Method_h__

#include "gxPointer.h"

class Method : public Pointer {
	public:
		enum Members {
			kCountOfMembers
		};
		enum Constants {
			kCountOfConstants
		};
		static const Type		type;
		static const Interface	interface;
		static void init();
		Method(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Method() {}
};

#endif // __Method_h__
