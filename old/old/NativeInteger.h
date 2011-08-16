#ifndef __NativeInteger_h__
#define __NativeInteger_h__

#include "Instance.h"
#include "BuiltInTypes.h"

class NativeInteger : public Instance {
	public:
		typedef int32_t	Integer;
		NativeInteger(Integer constantValue= 0);
		Integer value() const;
	protected:
		virtual ~NativeInteger();
	private:
		Integer	_value;
};

inline NativeInteger::NativeInteger(Integer constantValue)
	:Instance(builtInTypes[tNativeInteger]), _value(constantValue) {
}
inline NativeInteger::Integer NativeInteger::value() const {
	return _value;
}
inline NativeInteger::~NativeInteger() {
}

#endif // __NativeInteger_h__
