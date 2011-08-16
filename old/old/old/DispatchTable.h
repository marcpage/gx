#ifndef _DispatchTable_h_
#define _DispatchTable_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include <vector>

/** 
	implementations are filled in, in order:
	
		1. Current Type, on up
		2. Behavior, on up
		3. Library by Type name, on up
		4. Library by Behavior name, on up
		5. Internal Library by Type_<name> on up
		6. Internal Library by Behavior_<name> on up
*/
class DispatchTable : public ReferenceCounted {
	public:
		typedef DispatchTablePtr	Ptr;
		static Ptr create(BehaviorParam behavior);
		DispatchTable &add(ImplementationParam implementation);
		DispatchTable &set(StringParam name, ImplementationParam implementation);
		ImplementationParam get(size_t index) const;
		ImplementationParam get(StringParam name) const;
		BehaviorParam behavior() const;
	protected:
		DispatchTable();
		DispatchTable(const DispatchTable &other);
		DispatchTable &operator=(const DispatchTable &other);
	private:
		typedef std::vector<ImplementationPtr>	ImplementationList;
		BehaviorPtr			_behavior;
		ImplementationList	_implementations;
		virtual ~DispatchTable();
};

#endif // _DispatchTable_h_
