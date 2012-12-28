#ifndef _SubString_h_
#define _SubString_h_

#include "String.h"

class SubString : public String {
	public:
		static Ptr create(StringParam theString, size_t offset);
		static Ptr create(StringParam theString, size_t offset, size_t length);
		virtual uint32_t at(size_t index) const;
		virtual size_t find(StringParam substring) const;
		virtual size_t find(StringParam substring, size_t offset) const;
		virtual size_t findFromEnd(StringParam substring) const;
		virtual size_t findFromEnd(StringParam substring, size_t offset) const;
		virtual std::string &convert(std::string &buffer);
		virtual size_t length() const;
		virtual size_t parts() const;
	protected:
		SubString(); ///< Prevent usage
		SubString(const SubString &other); ///< Prevent usage
		SubString &operator=(const SubString &other); ///< Prevent usage
		SubString(StringParam master, size_t offset, size_t length);
	private:
		Ptr		_master;
		size_t	_offset;
		size_t	_length;
		virtual ~SubString();
};

#include "SubString.hpp"

#endif // _SubString_h_
