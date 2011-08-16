#ifndef __CodeGenericInstance_h__
#define __CodeGenericInstance_h__

#include "gxForwardDeclare.h"

class CodeGenericInstance {
	public:
		CodeGenericInstance();
		virtual void call(const Pointer &context, const List &inputs, List &outputs)= 0;
	protected:
		virtual ~CodeGenericInstance();
};

#endif // __CodeGenericInstance_h__
