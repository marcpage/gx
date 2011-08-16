#ifndef __NativeInstance_h__
#define __NativeInstance_h__

#include <vector>
#include "BuiltInTypes.h"
#include "Instance.h"
#include "NativeInteger.h"
#include "NativeInstance.h"
#include "posix/MessageException.h"

class NativeInstance : public Instance {
	public:
		typedef NativeInteger::Integer	Index;
		NativeInstance(NativeInstanceParam type);
		Index members() const;
		InstanceParam member(Index index) const;
		NativeInstanceRef member(Index index, InstanceParam value);
		InstanceRef &member(Index index);
	protected:
		virtual ~NativeInstance();
	private:
		typedef std::vector<InstanceRef>	InstanceList;
		InstanceList	_members;
		friend void initBuiltInTypes();
		NativeInstance(Index memberCount);
		InstanceList::size_type	_memberCount(NativeInstanceRef typeToEvaluate);
};

inline NativeInstance::NativeInstance(NativeInstanceParam instanceType)
	:Instance(instanceType), _members(_memberCount(instanceType)) {
}
inline NativeInstance::Index NativeInstance::members() const {
	return _members.size();
}
inline InstanceParam NativeInstance::member(Index index) const {
	AssertMessageException(index >= 0);
	AssertMessageException(index < static_cast<Index>(_members.size()));
	return _members[index];
}
inline NativeInstanceRef NativeInstance::member(Index index, InstanceParam value) {
	NativeInstance							*modify= this;
	exec::ReferenceCounted::RetainAction	action= exec::ReferenceCounted::Retain;
	
	AssertMessageException(index >= 0);
	AssertMessageException(index < static_cast<Index>(_members.size()));
	if(references() != 1) {
		modify= new NativeInstance(type());
		modify->_members= _members;
		action= exec::ReferenceCounted::DoNotRetain;
	}
	modify->_members[index]= value;
	return NativeInstanceRef(modify, action);
}
InstanceRef &member(Index index) {
	AssertMessageException(references() == 1);
	return _members[index];
}
inline NativeInstance::~NativeInstance() {
}
inline NativeInstance::InstanceList::size_type	NativeInstance::_memberCount(NativeInstanceRef typeToEvaluate) {
	InstanceList::size_type	count= 0;
	
	while(typeToEvaluate) {
		AssertMessageException(typeToEvaluate->type() == builtInTypes[tType]);
		InstanceRef	memberList= typeToEvaluate->member(3);
		AssertMessageException(memberList->type() == builtInTypes[tNativeInstanceList]);
		NativeInstanceList	*memberListPtr= reinterpret_cast<NativeInstanceList*>(memberList.operator->());
		count+= memberListPtr->size();
		InstanceRef	parent= typeToEvaluate->member(1);
		AssertMessageException( (!parent) || (parent->type() == builtInTypes[tType]) );
		if(parent) {
			typeToEvaluate.assign(reinterpret_cast<NativeInstance*>(parent.operator->()));
		} else {
			typeToEvaluate.assign(NULL);
		}
	}
	return count;
}
inline NativeInstance::NativeInstance(NativeInstance::Index memberCount)
	:Instance(NativeInstanceRef()), _members(memberCount) {
}

#endif // __NativeInstance_h__
