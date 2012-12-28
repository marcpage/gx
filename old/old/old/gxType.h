#ifndef __Type_h__
#define __Type_h__

#include "gxPointer.h"

class Type : public Pointer {
	public:
		enum TypeMembers {
			Name,
			Parent,
			Dispatches,
			Constants,
			Members,
			kCountOfMembers
		};
		enum Constants {
			AllTypes,
			kCountOfConstants
		};
		static const Type		type;
		static const Interface	interface;
		static void init();
		Type(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain):Pointer(instance, action) {}
		~Type() {}
};

#endif // __Type_h__
