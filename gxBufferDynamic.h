#ifndef __gxBufferDynamic_h__
#define __gxBufferDynamic_h__

#include "gxBuffer.h"
#include <stdint.h>
#include <string>
#include <string.h>

namespace gx {

	class BufferDynamic : public Buffer {
		public:
			typedef Buffer						Super;
			typedef Base::Ptr<BufferDynamic>	Ptr;
			BufferDynamic(type::Type *type, const char *string= NULL);
			BufferDynamic(type::Type *type, Buffer *buffer);
			BufferDynamic(type::Type *type, void *buffer, uintptr_t size, bool isreadonly);
			virtual uintptr_t size();
			virtual uint8_t &at(uintptr_t byte);
			virtual bool readonly() const;
			virtual void *contiguous(uintptr_t start, uintptr_t count);
			virtual void copyTo(uintptr_t start, uintptr_t count, void *buffer);
			std::string &internals();
		protected:
			virtual ~BufferDynamic();
			virtual void free();
		private:
			std::string	_buffer;
	};

	inline BufferDynamic::BufferDynamic(type::Type *type, const char *string= NULL)
			:Super(type),_buffer(NULL == string ? "" : string) {}
	inline BufferDynamic::BufferDynamic(type::Type *type, Buffer *buffer)
			:Super(type),_buffer(buffer->size(), '\0') {
		buffer->copyTo(const_cast<char*>(_buffer.data()), 0, buffer.size());
	}
	inline BufferDynamic::BufferDynamic(type::Type *type, void *buffer, uintptr_t size, bool isreadonly)
			:Super(_type),_buffer(buffer),_size(size) {}
	inline uintptr_t BufferDynamic::size() {return _buffer.size();}
	inline uint8_t &BufferDynamic::at(uintptr_t byte) {
		// assert(byte < _buffer.size())
		return reinterpret_cast<uint8_t>(const_cast<char*>(_buffer.data()))[byte];
	}
	inline bool BufferDynamic::readonly() const {return false;}
	inline void *BufferDynamic::contiguous(uintptr_t start, uintptr_t count) {
		// assert(start+count < _buffer.size())
		return &reinterpret_cast<uint8_t>(const_cast<char*>(_buffer.data()))[start];
	}
	inline void BufferDynamic::copyTo(uintptr_t start, uintptr_t count, void *buffer) {
		// assert(start+count < _buffer.size())
		memcpy(buffer, &_buffer->data()[start], count);
	}
	inline BufferDynamic::~BufferDynamic() {}
	inline void BufferDynamic::free() {Super::free();}
	inline std::string &internals() {return _buffer;}

}

#endif // __gxBufferDynamic_h__
