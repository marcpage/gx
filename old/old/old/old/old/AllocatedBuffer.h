#ifndef _AllocatedBuffer_h_
#define _AllocatedBuffer_h_

#include "Buffer.h"
#include <string>

class AllocatedBuffer : public Buffer {
	public:
		static AllocatedBufferPtr create(const void * const buffer, size_t theLength);
		static AllocatedBufferPtr serialize(const Ptr &buffer);
		virtual const Byte &operator[](size_t index) const;
		virtual size_t length() const;
		virtual uint32_t parts() const;
		const Byte *data() const;
	private:
		AllocatedBuffer();
		AllocatedBuffer(const void *buffer, size_t length);
		AllocatedBuffer(const AllocatedBuffer &other);
		AllocatedBuffer &operator=(const AllocatedBuffer &other);
	private:
		typedef std::string	Storage;
		Storage	_buffer;
		virtual ~AllocatedBuffer();
};

#endif // _AllocatedBuffer_h_
