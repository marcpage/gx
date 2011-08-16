#ifndef __gxPrototype_h__
#define __gxPrototype_h__

#include "gxPointer.h"

namespace gx {

	class Prototype : public Pointer {
		public:
			Prototype();
			Prototype(Instance *instance, Pointer::RetainAction action);
			~Prototype();
		protected:
	};

} // namespace gx

#endif // __gxPrototype_h__
