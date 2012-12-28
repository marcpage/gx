#ifndef __IntrinsicNativeCode_h__
#define __IntrinsicNativeCode_h__

#include "gxIntrinsicCode.h"

class IntrinsicNativeCode : public IntrinsicCode {
	public:
		typedef void (*Call)(const Pointer &context, const List &inputs, List &outputs);
		IntrinsicNativeCode(Call call);
		virtual void call(const Pointer &context, const List &inputs, List &outputs);
	protected:
		virtual ~IntrinsicNativeCode();
	private:
		Call	_code;
};

#endif // __IntrinsicNativeCode_h__
