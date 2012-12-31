#ifndef __gxMethod_h__
#define __gxMethod_h__

#include <string>
#include "gxInstance.h"
#include "gxExecParameters.h"

namespace type {
	class Prototype;
}
namespace exec {
	class Queue;
}

namespace gx {

	class Method : public Instance {
		public:
			typedef Instance			Super;
			typedef Base::Ptr<Method>	Ptr;
			Method(type::Type *type, const std::string &name, type::Prototype *prototype);
			virtual void start(Queue *queue, exec::Parameters &inputs, exec::Parameters &outputs)=0;
			type::Prototype *getPrototype();
			const type::Prototype *getPrototype() const;
		protected:
			virtual ~Method();
			virtual void free();
		private:
			std::string		_name;
			type::Prototype	*_prototype;
	};

	inline Method::Method(type::Type *type, const std::string &name, type::Prototype *prototype)
			:Super(type),_name(name),_prototype(prototype) {}
	inline type::Prototype *Method::getPrototype() {return _prototype;}
	inline const type::Prototype *Method::getPrototype() const {return _prototype;}
	inline Method::~Method() {}
	inline void Method::free() {Super::free();}

}

#endif // __gxMethod_h__
