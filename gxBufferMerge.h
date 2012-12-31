#ifndef __gxBufferMerge_h__
#define __gxBufferMerge_h__

#include "gxBuffer.h"
#include <stdint.h>
#include <vector>

namespace gx {

	class BufferMerge : public Buffer {
		public:
			typedef std::vector<Buffer*>	List;
			typedef Buffer					Super;
			typedef Base::Ptr<BufferMerge>	Ptr;
			BufferMerge(type::Type *type, Buffer *buffer, uintptr_t offset, uintptr_t size);
			virtual uintptr_t size();
			virtual uint8_t &at(uintptr_t byte);
			virtual bool readonly() const;
			virtual void *contiguous(uintptr_t start, uintptr_t count);
			virtual void copyTo(uintptr_t start, uintptr_t count, void *buffer);
			List &buffers();
			void add(Buffer *buffer, uint32_t index);
			void remove(uint32_t index);
		protected:
			virtual ~BufferMerge();
			virtual void free();
		private:
			List	_buffers;
	};

	inline BufferMerge::BufferMerge(type::Type *type)
			:Super(_type),_buffer(buffer),_offset(offset),_size(size) {
		// assert(offset+size < buffer->size())
	}
	inline uintptr_t BufferMerge::size() {
		uintptr_t	size= 0;

		for(List::iterator buffer= _buffers.begin(); buffer != _buffers.end(); ++buffer) {
			if(NULL != *buffer) {
				size+= (*buffer)->size();
			}
		}
		return size;
	}
	inline uint8_t &BufferMerge::at(uintptr_t byte) {
		for(List::iterator buffer= _buffers.begin(); buffer != _buffers.end(); ++buffer) {
			if(NULL != *buffer) {
				uintptr_t	bufferSize= (*buffer)->size();

				if(byte > bufferSize) {
					byte-= bufferSize;
				} else {
					return (*buffer)->at(byte);
				}
			}
		}
		// assert(false)
		return _buffers[0]->at(0);
	}
	inline bool BufferMerge::readonly() const {return true;}
	inline void *BufferMerge::contiguous(uintptr_t start, uintptr_t count) {
		for(List::iterator buffer= _buffers.begin(); buffer != _buffers.end(); ++buffer) {
			if(NULL != *buffer) {
				uintptr_t	bufferSize= (*buffer)->size();

				if(start > bufferSize) {
					start-= bufferSize;
				} else if(start+count <= bufferSize) {
					return (*buffer)->contiguous(start, count);
				} else {
					return NULL;
				}
			}
		}
		// assert(false)
		return NULL;
	}
	inline void BufferMerge::copyTo(uintptr_t start, uintptr_t count, void *buffer) {
		for(List::iterator buffer= _buffers.begin(); (count > 0) && (buffer != _buffers.end()); ++buffer) {
			if(NULL != *buffer) {
				uintptr_t	bufferSize= (*buffer)->size();

				if(start > bufferSize) {
					start-= bufferSize;
				} else {
					const uintptr_t	toCopy= (start + count) > bufferSize ? bufferSize - start : count;

					(*buffer)->copyTo(start, toCopy, buffer);
					start= 0;
					count-= toCopy;
				}
			}
		}
		// assert(count == 0)
	}
	inline BufferMerge::~BufferMerge() {
		for(List::iterator buffer= _buffers.begin(); buffer != _buffers.end(); ++buffer) {
			if(NULL != *buffer) {
				(*buffer)->release();
			}
		}
	}
	inline void BufferMerge::free() {Super::free();}
	inline List &BufferMerge::buffers() {return _buffers;}
	inline void BufferMerge::add(Buffer *buffer, uint32_t index) {
		if(index >= _buffers.size()) {
			_buffers.append(buffer);
		} else {
			_buffers.insert(_buffers.begin()+index, buffer);
		}
		buffer->retain();
	}
	inline void BufferMerge::remove(uint32_t index) {
		// assert(index < _buffers.size())
		if(NULL != _buffers[index]) {
			_buffers[index]->release();
			_buffers.erase(_buffers.begin()+index);
		}
	}

}

#endif // __gxBufferMerge_h__
