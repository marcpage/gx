#ifndef _Named_h_
#define _Named_h_

#include "ForwardDeclares.h"
#include "ReferenceCounted.h"

template<class T>
class Named : public ReferenceCounted {
	public:
		typedef SmartPtr<Named<T> >	Ptr;
		static Ptr create(StringParam theName, T *theItem);
		StringParam name() const;
		const SmartPtr<T> &item() const;
	protected:
		Named();
		Named(StringParam theName, T *theItem);
		Named(const Named &other);
		Named &operator=(const Named &other);
	private:
		StringPtr	_name;
		SmartPtr<T>	_item;
		virtual ~Named();
};

#endif // _Named_h_
