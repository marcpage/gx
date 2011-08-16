#ifndef __NativeMethod_h__
#define __NativeMethod_h__

class NativeMethod : public Method {
	public:
		typedef void (*Method)(List &inputs, List &outputs);
		NativeMethod(Method implementation= NULL);
	protected:
		virtual ~NativeMethod();
};

#endif // __NativeMethod_h__
