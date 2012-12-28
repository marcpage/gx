#ifndef __Instance_h__
#define __Instance_h__

#include "gxPointer.h"

class Instance : public Pointer {
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
		Instance(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Instance() {}
};

#endif // __Instance_h__
