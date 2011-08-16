#ifndef __Reference_h__
#define __Reference_h__

#include "gxPointer.h"

class Reference : public Pointer {
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
		Reference(const Pointer &value);
		Reference(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Reference();
};

#endif // __Reference_h__
