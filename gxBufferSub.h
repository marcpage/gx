#ifndef __gxBufferSub_h__
#define __gxBufferSub_h__

#include "gxBuffer.h"
#include <stdint.h>

namespace gx {

	class BufferSub : public Buffer {
		public:
			typedef Buffer					Super;
			typedef Base::Ptr<BufferSub>	Ptr;
			BufferSub(type::Type *type, Buffer *buffer, uintptr_t offset, uintptr_t size);
			virtual uintptr_t size();
			virtual uint8_t &at(uintptr_t byte);
			virtual bool readonly() const;
			virtual void *contiguous(uintptr_t start, uintptr_t count);
			virtual void copyTo(uintptr_t start, uintptr_t count, void *buffer);
		protected:
			virtual ~BufferSub();
			virtual void free();
		private:
			Buffer		*_buffer;
			uintptr_t	_offset;
			uintptr_t	_size;
	};

	inline BufferSub::BufferSub(type::Type *type, Buffer *buffer, uintptr_t offset, uintptr_t size)
			:Super(_type),_buffer(buffer),_offset(offset),_size(size) {
		_buffer->retain();
		// assert(offset+size < buffer->size())
	}
	inline uintptr_t BufferSub::size() {return _size;}
	inline uint8_t &BufferSub::at(uintptr_t byte) {
		// assert(byte < _buffer.size())
		return _buffer->at(byte - offset);
	}
	inline bool BufferSub::readonly() const {return true;}
	inline void *BufferSub::contiguous(uintptr_t start, uintptr_t count) {
		// assert(start+count < buffer->size())
		return _buffer->contiguous(start - _offset, count);
	}
	inline void BufferSub::copyTo(uintptr_t start, uintptr_t count, void *buffer) {
		// assert(start+count < buffer->size())
		_buffer->copyTo(start - _offset, count, buffer);
	}
	inline BufferSub::~BufferSub() {_buffer->release();}
	inline void BufferSub::free() {Super::free();}

}

#endif // __gxBufferSub_h__
