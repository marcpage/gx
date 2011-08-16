#ifndef _JoinString_h_
#define _JoinString_h_

#include "String.h"

class JoinString : public String {
	public:
		static Ptr create(const Ptr &string1, const Ptr &string2);
		virtual uint32_t at(size_t index) const;
		virtual size_t find(const Ptr &substring) const;
		virtual size_t find(const Ptr &substring, size_t offset) const;
		virtual size_t findFromEnd(const Ptr &substring) const;
		virtual size_t findFromEnd(const Ptr &substring, size_t offset) const;
		virtual std::string &convert(std::string &buffer);
		virtual size_t length() const;
		virtual size_t parts() const;
	protected:
		JoinString();
		JoinString(const JoinString &other);
		JoinString &operator=(const JoinString &other);
	private:
		Ptr		_string1;
		Ptr		_string2;
		virtual ~JoinString();
};

#endif // _JoinString_h_
