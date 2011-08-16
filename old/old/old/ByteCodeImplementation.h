#ifndef _ByteCodeImplementation_h_
#define _ByteCodeImplementation_h_

#include "Implementation.h"

class ByteCodeImplementation : public Implementation {
	public:
		Ptr create(BufferParam buffer);
	protected:
		ByteCodeImplementation();
		ByteCodeImplementation(BufferParam bytecode);
		ByteCodeImplementation(const ByteCodeImplementation &other);
		ByteCodeImplementation &operator=(const ByteCodeImplementation &other);
	private:
		BufferPtr	_bytecode;
		virtual ~ByteCodeImplementation();
};

#endif // _ByteCodeImplementation_h_
