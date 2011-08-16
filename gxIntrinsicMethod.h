#ifndef __gxIntrinsicMethod_h__
#define __gxIntrinsicMethod_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxText.h"
#include <vector>

namespace gx {

	class IntrinsicMethod : public Intrinsic {
		public:
			IntrinsicMethod(const Text &theName, const Prototype &thePrototype);
			const Prototype &prototype() const;
			const Text &name() const;
			virtual void execute(Pointer &context, const List &inputs, List &outputs);
		protected:
			virtual ~IntrinsicMethod();
		private:
			Text		_name;
			Prototype	_prototype
	};

} // namespace gx

#endif // __gxIntrinsicMethod_h__
