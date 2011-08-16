#ifndef __gxIntrinsicNativeMethod_h__
#define __gxIntrinsicNativeMethod_h__

#include "gxIntrinsic.h"
#include "gxType.h"
#include "gxInterface.h"
#include "gxText.h"
#include <vector>

namespace gx {

	class IntrinsicNativeMethod : public IntrinsicMethod {
		public:
			typedef void (NativeCode*)(Pointer &context, const List &inputs, List &outputs);
			IntrinsicNativeMethod(const Text &name, const Prototype &prototype, NativeCode code);
			virtual void execute(Pointer &context, const List &inputs, List &outputs);
		protected:
			virtual ~IntrinsicNativeMethod();
		private:
			NativeCode	_code;
	};

} // namespace gx

#endif // __gxIntrinsicNativeMethod_h__
