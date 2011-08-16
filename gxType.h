#ifndef __gxType_h__
#define __gxType_h__

#include "gxPointer.h"

namespace gx {

	class Type : public Pointer {
		public:
			Type();
			Type(Instance *instance, Pointer::RetainAction action);
			~Type();
		protected:
	};

} // namespace gx

#endif // __gxType_h__
