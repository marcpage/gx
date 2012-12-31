#ifndef __gxUtilityies_h__
#define __gxUtilityies_h__

#include <string>
#include <ctype>

namespace util {

	template<typename T> assignAndReturnOriginal(T &variable, T value) {
		T	oldValue= variable;

		variable= value;
		return oldValue;
	}

	template<typename String> bool equalsIgnoreCase(const String &s1, const String &s2) {
		if(s1.size() != s2.size()) {
			return false;
		}
		for(std::string::const_iterator c1= s1.begin(),c2= s2.begin(); c1 != s1.end(); ++c1, ++c2) {
			if(std::tolower(*c1) != std::tolower(*c2)) {
				return false;
			}
		}
		return true;
	}

}

#endif // __gxUtilityies_h__
