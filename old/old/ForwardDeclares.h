#ifndef __ForwardDeclares_h__
#define __ForwardDeclares_h__

#include <stdint.h>
#include "InstanceReference.h"

#define ForwardDeclare(x) \
	class x; \
	typedef InstanceReference<x> x##Ref; \
	typedef const InstanceReference<x> &x##Param;
	ForwardDeclare(Instance);
	ForwardDeclare(NativeInteger);
	ForwardDeclare(NativeMethod);
	ForwardDeclare(NativeInstanceList);
	ForwardDeclare(NativeString);
	ForwardDeclare(NativeInstance);
#undef Ref

#endif // __ForwardDeclares_h__
