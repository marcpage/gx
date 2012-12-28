#ifndef _Implementation_h_
#define _Implementation_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"

/** 
	Interface class
*/
class Implementation : public ReferenceCounted {
	protected:
		typedef ImplementationPtr	Ptr;
		Implementation();
		Implementation(const Implementation &other);
		Implementation &operator=(const Implementation &other);
	private:
		virtual ~Implementation();
};

#endif // _Implementation_h_
