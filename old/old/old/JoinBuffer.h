#ifndef _JoinBuffer_h_
#define _JoinBuffer_h_

#include "Buffer.h"

class JoinBuffer : public Buffer {
	public:
		static Ptr create(const Ptr &b1, const Ptr &b2);
		virtual const Byte &operator[](size_t index) const;
		virtual size_t length() const;
		virtual uint32_t parts() const;
	protected:
		JoinBuffer();
		JoinBuffer(const Ptr &buffer1, const Ptr &buffer2);
		JoinBuffer(const JoinBuffer &other);
		JoinBuffer &operator=(const JoinBuffer &other);
	private:
		Ptr	_buffer1;
		Ptr	_buffer2;
		virtual ~JoinBuffer();
};

#endif // _JoinBuffer_h_
