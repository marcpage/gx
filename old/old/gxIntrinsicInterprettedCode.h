#ifndef __IntrinsicCode_h__
#define __IntrinsicCode_h__

#include "gxIntrinsicCode.h"

class IntrinsicInterprettedCode : public IntrinsicCode {
	public:
		IntrinsicInterprettedCode(const Buffer &instructions);
		virtual void call(const Pointer &context, const List &inputs, List &outputs);
	protected:
		virtual ~IntrinsicInterprettedCode();
	private:
		Buffer	_instructions;
};

#endif // __IntrinsicInterprettedCode_h__
