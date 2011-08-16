#ifndef __Prototype_h__
#define __Prototype_h__

#include "gxPointer.h"

class Prototype : public Pointer {
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
		Prototype(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Prototype() {}
};

#endif // __Prototype_h__
