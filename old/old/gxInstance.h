#ifndef __gxInstance_h__
#define __gxInstance_h__

#include "gxForwards.h"
#include "gxType.h"
#include "posix/ExecutionReferenceCounted.h"

namespace gx {

	class Instance : public exec::ReferenceCounted {
		public:
			Instance(const Type &actualType);
			bool is(const Type &actualType);
			bool does(const Interface &interface);
			template<class T> T* modifiableCopy();
			const Type &type() const;
		protected:
			virtual ~Instance();
			virtual Instance *clone();
		private:
			friend class TypeSystem;
			Type	_type;
	};

} // namespace gx

#endif // __gxGenericInstance_h__
