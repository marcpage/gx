#ifndef __NativeCode_h__
#define __NativeCode_h__

#include "gxCode.h"

class NativeCode : public Code {
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
		NativeCode(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~NativeCode() {}
};

#endif // __NativeCode_h__
