#ifndef __Dispatch_h__
#define __Dispatch_h__

#include "gxPointer.h"

class Dispatch : public Pointer {
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
		Dispatch(Interface useInterface);
		Dispatch(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Dispatch() {}
		
};

#endif // __Dispatch_h__
