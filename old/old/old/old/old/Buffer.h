#ifndef _Buffer_h_
#define _Buffer_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"

/** 
	Interface class
*/
class Buffer : public ReferenceCounted {
	public:
		typedef unsigned char	Byte;
		typedef BufferPtr		Ptr;
		virtual const Byte &operator[](size_t index) const= 0;
		virtual size_t length() const= 0;
		virtual uint32_t parts() const= 0;
		BufferPtr remove(size_t offset, size_t length);
		BufferPtr add(const BufferPtr &other);
	protected:
		Buffer();
		Buffer(const Buffer &other);
		Buffer &operator=(const Buffer &other);
		virtual ~Buffer();
};

BufferPtr operator+(BufferParam b1, BufferParam b2);

#include "Buffer.hpp"

#endif // _Buffer_h_
