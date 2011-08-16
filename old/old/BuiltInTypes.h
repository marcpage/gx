#ifndef __BuiltInTypes_h__
#define __BuiltInTypes_h__

#include "ForwardDeclares.h"

enum BuiltInTypes {
	tType,
	tObject,
	tNativeInteger,
	tNativeMethod,
	tNativeString,
	tNativeInstanceList,
	tBehavior,
	tNamedType,
	tMethod,
	tDispatchTable,
	NumberOfBuiltInTypes
};

extern NativeInstanceRef *builtInTypes;

void initBuiltInTypes();
void cleanupBuiltInTypes();

class BuiltInTypesScope {
	public:
		BuiltInTypesScope();
		~BuiltInTypesScope();
};

inline BuiltInTypesScope::BuiltInTypesScope() {
	initBuiltInTypes();
}
inline BuiltInTypesScope::~BuiltInTypesScope() {
	cleanupBuiltInTypes();
}

#endif // __BuiltInTypes_h__
