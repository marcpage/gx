#ifndef _NativeImplementation_h_
#define _NativeImplementation_h_

#include "Implementation.h"

class NativeImplementation : public Implementation {
	protected:
		NativeImplementation();
		NativeImplementation(const NativeImplementation &other);
		NativeImplementation &operator=(const NativeImplementation &other);
	private:
		virtual ~NativeImplementation();
};

#endif // _NativeImplementation_h_
