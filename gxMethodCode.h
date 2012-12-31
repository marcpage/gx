#ifndef __gxMethodCode_h__
#define __gxMethodCode_h__

#include "gxMethodNative.h"
#include "gxBuffer.h"

namespace gx {

	class MethodCode : public MethodNative {
		public:
			typedef MethodNative			Super;
			typedef Base::Ptr<MethodCode>	Ptr;
			MethodCode(type::Type *type, const std::string &name, type::Prototype *prototype, Buffer *code);
			virtual void start(Queue *queue, exec::Parameters &inputs, exec::Parameters &outputs);
		protected:
			virtual ~Method();
			virtual void free();
		private:
			Buffer	*_code;
			static void _interpret(Queue *, exec::Parameters &inputs, exec::Parameters &outputs);
			uint64_t _getNumber(uintptr_t &index) {
				uint64_t	value= 0;
				uint8_t		byte;

				do	{
					byte= _code.at(index++);
					value= (value << 7) | (byte & ~0x80);
				} while( (byte & 0x80) == 0x80 );
				return value;
			}
	};

	inline MethodCode::MethodCode(type::Type *type, const std::string &name, type::Prototype *prototype, Buffer *code)
			:Super(type),_name(name),_prototype(prototype),_code(code) {}
	inline void start(Queue *queue, exec::Parameters &inputs, exec::Parameters &outputs) {
		Super::start(queue, inputs, outputs);
	}
	inline MethodCode::~MethodCode() {}
	inline void MethodCode::free() {Super::free();}
	/**
		1 loaddata(size, buffer)
		2 loadtype(name)
		3 loadfunction(type,name)
		4 loadbehavior(name)
		5 findmethod(behavior,name)
		6 cast(object,behavior)
		7 loadmethodfunction(object,index)
		8 call(function,inputcount,*inputs,outputcount)
		9 getbehavior(object)
		10 loadinput(index)
		11 return(count,*results)
	*/
	inline void MethodCode::_interpret(Queue *, exec::Parameters &inputs, exec::Parameters &outputs) {
		uintptr_t	ip= 0;
		std::string	buffer;

		while(ip < _code.size()) {
			uint64_t	code= _getNumber(ip);
			uint64_t	size;

			switch(code) {
				case 0:	break; // noop
				case 1: // load data: count, bytes
					size= _getNumber(ip);

					break;
				default:
					break;

			}
		}
	}

}

#endif // __gxMethodCode_h__
