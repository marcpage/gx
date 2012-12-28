#ifndef __NativeString_h__
#define __NativeString_h__

#include <string>
#include "Instance.h"
#include "BuiltInTypes.h"
#include "NativeInteger.h"

class NativeString : public Instance {
	public:
		typedef NativeInteger::Integer	Index;
		NativeString(const char *valueStr= NULL);
		const std::string &value() const;
		Index size() const;
	protected:
		virtual ~NativeString();
	private:
		std::string	_str;
};

inline NativeString::NativeString(const char *valueStr)
	:Instance(builtInTypes[tNativeString]), _str(NULL == valueStr ? "" : valueStr) {
}
inline const std::string &NativeString::value() const {
	return _str;
}
inline NativeString::Index NativeString::size() const {
	return _str.size();
}
inline NativeString::~NativeString() {
}

#endif // __NativeString_h__
