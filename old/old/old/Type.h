#ifndef _Type_h_
#define _Type_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include "InstanceRef.h"
#include <vector>

class Type : public ReferenceCounted {
	public:
		typedef TypePtr	Ptr;
		static Ptr create(StringParam theName, TypeSystemParam system);
		StringParam name() const;
		size_t member(StringParam name) const;
		size_t behavior(BehaviorParam behavior) const;
		Type &add(StringParam name, BehaviorParam behavior);
		Type &add(DispatchTableParam dispatchTable);
		Type &add(const InstanceRef &constant);
		Type &add(StringParam name, ImplementationParam code);
	protected:
		Type();
		Type(StringParam name);
		Type(const Type &other);
		Type &operator=(const Type &other);
	private:
		typedef std::vector<SmartPtr<Named<Behavior> > >		NamedBehaviorList;
		typedef std::vector<SmartPtr<Named<Implementation> > >	NamedImplementationList;
		typedef std::vector<DispatchTablePtr >					DispatchTableList;
		typedef std::vector<InstanceRef>						InstanceList;
		StringPtr				_name;
		NamedBehaviorList		_members;
		DispatchTableList		_dispatch;
		InstanceList			_constants;
		NamedImplementationList	_blocks;
		virtual ~Type();
};

#endif // _Type_h_
