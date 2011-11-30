#ifndef _String_h_
#define _String_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include <string>

/** 
	Interface class
*/
class String : public ReferenceCounted {
	public:
		static const size_t	npos= static_cast<size_t>(-1);
		typedef StringPtr	Ptr;
		StringPtr substring(size_t offset);
		StringPtr substring(size_t offset, size_t length);
		StringPtr append(StringParam other);
		StringPtr remove(size_t offset);
		StringPtr remove(size_t offset, size_t length);
		StringPtr insert(StringParam substr, size_t beforeIndex);
		int compare(StringParam substr) const;
		StringPtr trimFromStart(size_t count);
		StringPtr trimFromEnd(size_t count);
		StringPtr strip();
		StringPtr stripStart();
		StringPtr stripEnd();
		StringPtr replaceAll(StringParam find, StringParam replace);
		virtual uint32_t at(size_t index) const= 0;
		virtual size_t find(StringParam substr) const;
		virtual size_t find(StringParam substr, size_t offset) const;
		virtual size_t findFromEnd(StringParam substr) const;
		virtual size_t findFromEnd(StringParam substr, size_t offset) const;
		/// One of the converts needs to be overriddent, or else infinite loops will occur
		virtual std::string &convert(std::string &buffer) const;
		/// One of the converts needs to be overriddent, or else infinite loops will occur
		virtual std::wstring &convert(std::wstring &buffer) const;
		virtual size_t length() const= 0;
		virtual size_t parts() const= 0;
		virtual StringPtr insert(uint32_t character, size_t beforeIndex) const;
	protected:
		String();
		String(const String &other);
		String &operator=(const String &other);
		virtual ~String();
	private:
};

StringPtr operator+(StringParam s1, StringParam s2);

#include "String.hpp"

#endif // _String_h_
