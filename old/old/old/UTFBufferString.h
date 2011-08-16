#ifndef _UTFBufferString_h_
#define _UTFBufferString_h_

#include "String.h"

class UTFBufferString {
	public:
		enum Endian {
			BigEndian,
			LittleEndian,
			NativeEndian
		}
		static Ptr create(BufferParam utfBuffer, Endian endian);
		static UTFBufferStringPtr serialize(const Ptr &string);
		virtual uint32_t at(size_t index) const;
		virtual std::wstring &convert(std::wstring &buffer);
		virtual size_t length() const;
		virtual size_t parts() const;
	protected:
		UTFBufferString();
		UTFBufferString(BufferParam utfBuffer, Endian endian);
		UTFBufferString(const UTFBufferString &other);
		UTFBufferString &operator=(const UTFBufferString &other);
	private:
		BufferPtr	_buffer;
		Endian		_endian;
		virtual ~UTFBufferString();
};

#include "UTFBufferString.hpp"

#endif // _UTFBufferString_h_
