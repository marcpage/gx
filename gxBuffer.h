#ifndef __gxBuffer_h__
#define __gxBuffer_h__

#include "gxInstance.h"
#include <stdint.h>

namespace gx {

	class Buffer : public Instance {
		public:
			typedef Instance			Super;
			typedef Base::Ptr<Buffer>	Ptr;
			Buffer(type::Type *type);
			virtual uintptr_t size()=0;
			virtual uint8_t &at(uintptr_t byte)=0;
			virtual bool readonly() const=0;
			virtual void *contiguous(uintptr_t start, uintptr_t count)=0;
			virtual void copyTo(uintptr_t start, uintptr_t count, void *buffer)=0;
		protected:
			virtual ~Buffer();
			virtual void free();
	};

	inline Buffer::Buffer(type::Type *type):Super(type) {}
	inline Buffer::~Buffer() {}
	inline void Buffer::free() {Super::free();}

}

#endif // __gxBuffer_h__
