#ifndef __Instance_h__
#define __Instance_h__

#include "ForwardDeclares.h"
#include "posix/ExecutionReferenceCounted.h"

class Instance : public exec::ReferenceCounted {
	public:
		Instance(NativeInstanceParam actualType);
		NativeInstanceRef type();
		NativeInstanceParam type() const;
	protected:
		virtual ~Instance();
	private:
		NativeInstanceRef	_type;
		friend void initBuiltInTypes();
};

inline Instance::Instance(NativeInstanceParam actualType)
	:_type(actualType) {
}
inline NativeInstanceRef Instance::type() {
	return _type;
}
inline Instance::~Instance() {
}

#endif // __Instance_h__
