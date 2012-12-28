#ifndef _Instance_h_
#define _Instance_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include "InstanceRef.h"
#include <vector>

class Instance : public ReferenceCounted {
	public:
		typedef InstancePtr	Ptr;
		static Ptr create(TypeParam theType);
		TypeParam type() const;
		size_t length() const;
		const InstanceRef &member(size_t index);
	protected:
		Instance();
		Instance(TypeParam theType);
		Instance(const Instance &other);
		Instance &operator=(const Instance &other);
	private:
		typedef std::vector<InstanceRef>	InstanceList;
		TypePtr			_type;
		InstanceList	_members;
		virtual ~Instance();
};

#endif // _Instance_h_
