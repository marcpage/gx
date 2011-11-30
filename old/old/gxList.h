#ifndef __List_h__
#define __List_h__

#include "gxPointer.h"

class List : public Pointer {
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
		List(size_t actualSize);
		List(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~List() {}
		size_t size() const;
		void get(size_t index, Pointer &value);
		void set(size_t index, const Pointer &value);
};

#endif // __List_h__
