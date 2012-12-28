#ifndef _ASCIIBufferString_h_
#define _ASCIIBufferString_h_

#include "String.h"

class ASCIIBufferString : public String {
	public:
		static StringPtr create(BufferParam asciiBuffer);
		static ASCIIBufferStringPtr serialize(StringParam string);
		virtual uint32_t at(size_t index) const;
		virtual std::string &convert(std::string &buffer);
		virtual size_t length() const;
		virtual size_t parts() const;
	protected:
		ASCIIBufferString();
		ASCIIBufferString(BufferParam asciiBuffer);
		ASCIIBufferString(const ASCIIBufferString &other);
		ASCIIBufferString &operator=(const ASCIIBufferString &other);
	private:
		BufferPtr	_buffer;
		virtual ~ASCIIBufferString();
};

#include "ASCIIBufferString.hpp"

#endif // _ASCIIBufferString_h_
