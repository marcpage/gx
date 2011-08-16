#ifndef _SubBuffer_h_
#define _SubBuffer_h_

#include "Buffer.h"

class SubBuffer : public Buffer {
	public:
		static Ptr create(const Ptr &buffer, size_t offset, size_t theLength);
		virtual const Byte &operator[](size_t index) const;
		virtual size_t length() const;
		virtual uint32_t parts() const;
	protected:
		SubBuffer();
		SubBuffer(BufferParam buffer, size_t offset);
		SubBuffer(BufferParam buffer, size_t offset, size_t length);
		SubBuffer(const SubBuffer &other);
		SubBuffer &operator=(const SubBuffer &other);
	private:
		BufferPtr	_buffer;
		size_t		_offset;
		size_t		_length;
		virtual ~SubBuffer();
};

#endif // _SubBuffer_h_
