#ifndef __Buffer_h__
#define __Buffer_h__

#include "gxPointer.h"

class Buffer : public Pointer {
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
		Buffer(size_t bufferSize);
		Buffer(const void *data, size_t bufferSize);
		Buffer(GenericInstance *instance= NULL, Pointer::RetainAction action= Retain);
		~Buffer() {}
		virtual const void *value() const;
		virtual const size_t size() const;
};

#endif // __Buffer_h__
