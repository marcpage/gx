#ifndef __NamedInstance_h__
#define __NamedInstance_h__

#include "gxPointer.h"

class NamedInstance : public Pointer {
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
		NamedInstance(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~NamedInstance() {}
};

#endif // __NamedInstance_h__
