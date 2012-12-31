#ifndef __gxBufferFixed_h__
#define __gxBufferFixed_h__

#include "gxBuffer.h"
#include <stdint.h>

namespace gx {

	class BufferFixed : public Buffer {
		public:
			typedef Buffer					Super;
			typedef Base::Ptr<BufferFixed>	Ptr;
			BufferFixed(type::Type *type, const char *string);
			BufferFixed(type::Type *type, void *buffer, uintptr_t size, bool isreadonly);
			virtual uintptr_t size();
			virtual uint8_t &at(uintptr_t byte);
			virtual bool readonly() const;
			virtual void *contiguous(uintptr_t start, uintptr_t count);
			virtual void copyTo(uintptr_t start, uintptr_t count, void *buffer);
		protected:
			virtual ~BufferFixed();
			virtual void free();
		private:
			void		*_buffer;
			uintptr_t	_size;
			bool		_readonly;
	};

	inline BufferFixed::BufferFixed(type::Type *type, const char *string)
			:Super(type),_buffer(string),_size(strlen(string)), _readonly(true) {}
	inline BufferFixed::BufferFixed(type::Type *type, void *buffer, uintptr_t size, bool isreadonly)
			:Super(_type),_buffer(buffer),_size(size),_readonly(isreadonly) {}
	inline uintptr_t BufferFixed::size() {return _size;}
	inline uint8_t &BufferFixed::at(uintptr_t byte) {
		// assert(byte < _size)
		return reinterpret_cast<uint8_t>(_buffer)[byte];
	}
	inline bool BufferFixed::readonly() const {return _readonly;}
	inline void *BufferFixed::contiguous(uintptr_t start, uintptr_t count) {
		// assert(start+count < _size)
		return &reinterpret_cast<uint8_t>(_buffer)[start];
	}
	inline void BufferFixed::copyTo(uintptr_t start, uintptr_t count, void *buffer) {
		// assert(start+count < _size)
		memcpy(buffer, &reinterpret_cast<uint8_t*>(_buffer)[start], count);
	}
	inline BufferFixed::~BufferFixed() {}
	inline void BufferFixed::free() {Super::free();}

}

#endif // __gxBufferFixed_h__
