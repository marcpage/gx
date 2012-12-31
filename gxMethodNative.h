#ifndef __gxMethodNative_h__
#define __gxMethodNative_h__

#include "gxMethod.h"

namespace gx {

	class MethodNative : public Method {
		public:
			typedef Method					Super;
			typedef Base::Ptr<MethodNative>	Ptr;
			typedef void (*Function)(Queue *, exec::Parameters &inputs, exec::Parameters &outputs);
			MethodNative(type::Type *type, const std::string &name, type::Prototype *prototype, Function function);
			virtual void start(Queue *queue, exec::Parameters &inputs, exec::Parameters &outputs);
		protected:
			virtual ~Method();
			virtual void free();
		private:
			Function	_function;
	};

	inline MethodNative::MethodNative(type::Type *type, const std::string &name, type::Prototype *prototype, Function function)
			:Super(type),_name(name),_prototype(prototype),_function(function) {}
	inline void start(Queue *queue, exec::Parameters &inputs, exec::Parameters &outputs) {
		_function(queue, inputs, outputs);
	}
	inline MethodNative::~MethodNative() {}
	inline void MethodNative::free() {Super::free();}

}

#endif // __gxMethodNative_h__
