#ifndef _Behavior_h_
#define _Behavior_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include <vector>

class Behavior : public ReferenceCounted {
	public:
		typedef BehaviorPtr	Ptr;
		static Ptr create(StringParam name);
		static Ptr create(StringParam name, const Ptr &parent);
		Behavior &add(InterfaceParam theInterface);
		StringParam name() const;
		size_t lookup(StringParam name) const;
		bool does(BehaviorParam behavior) const;
	protected:
		Behavior();
		Behavior(StringParam name);
		Behavior(StringParam name, const Ptr &parent);
		Behavior(const Behavior &other);
		Behavior &operator=(const Behavior &other);
	private:
		typedef std::vector<InterfacePtr >			InterfaceList;
		typedef std::vector<ImplementationPtr >		ImplementationList;
		typedef std::vector<SmartPtr<Named<Interface> > >	NamedInterfaceList;
		StringPtr			_name;
		Ptr					_parent;
		InterfaceList		_interfaces;
		ImplementationList	_implementations; ///< Do not reference any members, only call other interfaces
		virtual ~Behavior();
};

#endif // _Behavior_h_
