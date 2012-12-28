#ifndef __InterprettedCode_h__
#define __InterprettedCode_h__

#include "gxCode.h"

class InterprettedCode : public Code {
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
		InterprettedCode(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~InterprettedCode() {}
};

#endif // __InterprettedCode_h__
