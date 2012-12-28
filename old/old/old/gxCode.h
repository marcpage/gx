#ifndef __Code_h__
#define __Code_h__

#include "gxPointer.h"

class Code : public Pointer {
	public:
		Code(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Code() {}
};

#endif // __Code_h__
