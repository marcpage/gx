#ifndef __gxInterface_h__
#define __gxInterface_h__

#include "gxPointer.h"

namespace gx {

	class Interface : public Pointer {
		public:
			Interface();
			Interface(Instance *instance, Pointer::RetainAction action);
			~Interface();
		protected:
	};

} // namespace gx

#endif // __gxInterface_h__
