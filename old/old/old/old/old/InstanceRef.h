#ifndef _InstanceRef_h_
#define _InstanceRef_h_

#include "Instance.h"

class InstanceRef : InstancePtr {
	public:
		InstanceRef();
		InstanceRef(TypeParam theType);
		InstanceRef(const InstanceRef &other);
		~InstanceRef();
		InstanceRef &operator=(const InstanceRef &other);
		DispatchTableParam dispatch() const;
		InstanceRef &cast(BehaviorParam behavior);
	private:
		size_t	_behavior;
};

#endif // _InstanceRef_h_
