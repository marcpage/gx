#ifndef _ReferencedBuffer_h_
#define _ReferencedBuffer_h_

#include "Buffer.h"

class ReferencedBuffer : public Buffer {
	public:
		static BufferPtr create(const void *buffer, size_t theLength);
		virtual const Byte &operator[](size_t index) const;
		virtual size_t length() const;
		virtual uint32_t parts() const;
	protected:
		ReferencedBuffer();
		ReferencedBuffer(const void *buffer, size_t length);
		ReferencedBuffer(const ReferencedBuffer &other);
		ReferencedBuffer &operator=(const ReferencedBuffer &other);
		virtual ~ReferencedBuffer();
	private:
		const Byte * const	_buffer;
		size_t				_length;
};

#include "ReferencedBuffer.hpp"

#endif // _ReferencedBuffer_h_
