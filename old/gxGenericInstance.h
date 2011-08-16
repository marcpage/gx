#ifndef __GenericInstance_h__
#define __GenericInstance_h__

#include "gxForwardDeclares.h"
#include "posix/ExecutionReferenceCounted.h"

class GenericInstance : public exec::ReferenceCounted {
	public:
		GenericInstance(const Type &actualType);
		bool is(const Type &actualType);
		bool does(const Interface &interface);
		template<class T>
		T* modifiableCopy();
	protected:
		virtual ~GenericInstance();
		virtual GenericInstance *clone();
	private:
		GenericInstance	*_type;
		friend class Type; ///< To patch up _type during bootstrap
};

template<class T>
T* GenericInstance::modifiableCopy() {
	if(references() == 1) {
		return this;
	}
	return clone();
}

#endif // __GenericInstance_h__
