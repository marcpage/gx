#ifndef _TypeSystem_h_
#define _TypeSystem_h_

#include "ForwardDeclares.h"
#include "ReferenceCounted.h"
#include <vector>

class TypeSystem : public ReferenceCounted {
	public:
		typedef SmartPtr<TypeSystem>	Ptr;
		static Ptr create();
		TypeParam findType(StringParam name);
		BehaviorParam findBehavior(StringParam name);
		TypeSystem &add(TypeParam type);
		void remove(TypeParam type);
	protected:
		TypeSystem();
		TypeSystem(const TypeSystem &other);
		TypeSystem &operator=(const TypeSystem &other);
	private:
		typedef std::vector<TypePtr>	TList;
		TList	_list;
		virtual ~TypeSystem();
};

#endif // _TypeSystem_h_
