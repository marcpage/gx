#ifndef __IntrinsicBuffer_h__
#define __IntrinsicBuffer_h__

#include "gxIntrinsic.h"
#include <string> ///< For std::string

class IntrinsicBuffer : public Intrinsic {
	public:
		IntrinsicBuffer(size_t amount);
		IntrinsicBuffer(const void *data, size_t amount);
		IntrinsicBuffer(const std::string &data);
		const void *value() const;
		const size_t size() const;
	protected:
		virtual ~IntrinsicBuffer() {}
		virtual GenericInstance *clone();
	private:
		std::string	_value;
};

#endif // __IntrinsicBuffer_h__
