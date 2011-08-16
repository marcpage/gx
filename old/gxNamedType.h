#ifndef __NamedType_h__
#define __NamedType_h__

#include "gxPointer.h"

class NamedType : public Pointer {
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
		NamedType(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~NamedType() {}
};

#endif // __NamedType_h__
