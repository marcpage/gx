#ifndef __NativeInstanceList_h__
#define __NativeInstanceList_h__

#include <vector>
#include "BuiltInTypes.h"
#include "Instance.h"
#include "NativeInteger.h"
#include "posix/MessageException.h"

class NativeInstanceList : public Instance {
	public:
		typedef NativeInteger::Integer	Index;
		NativeInstanceList(Index sizeGuess= 0);
		Index size() const;
		InstanceParam at(Index index) const;
		NativeInstanceListRef remove(Index start= 0, Index count= -1);
		NativeInstanceListRef insert(InstanceParam value, Index before= 0);
		InstanceParam operator[](Index index) const;
		NativeInstanceListRef clear();
		NativeInstanceListRef append(InstanceParam value);
		NativeInstanceListRef push(InstanceParam value);
		NativeInstanceListRef pop(InstanceRef &value);
		NativeInstanceListRef replace(Index at, InstanceRef value);
	protected:
		virtual ~NativeInstanceList();
	private:
		typedef exec::ReferenceCounted::RetainAction	RetainAction;
		typedef std::vector<InstanceRef>	InstanceList;
		InstanceList	_list;
		friend void initBuiltInTypes();
		void _modifiable(NativeInstanceList *&modifiable, RetainAction &action);
		void _validateAndFixIndex(Index &index) const;
};

NativeInstanceList::NativeInstanceList(Index sizeGuess)
	:Instance(builtInTypes[tNativeInstanceList]), _list() {
	if(sizeGuess > 0) {
		_list.reserve(sizeGuess);
	}
}
NativeInstanceList::Index NativeInstanceList::size() const {
	return _list.size();
}
InstanceParam NativeInstanceList::at(Index index) const {
	_validateAndFixIndex(index);
	return _list[index];
}
NativeInstanceListRef NativeInstanceList::remove(Index start, Index count) {
	NativeInstanceList	*modify= NULL;
	RetainAction		action= exec::ReferenceCounted::Retain;
	
	_validateAndFixIndex(start);
	if(0 == count) {
		return NativeInstanceListRef(this);
	}
	if(count < 0) {
		count= _list.size();
	}
	if(count + start > static_cast<Index>(_list.size())) {
		count= _list.size() - start;
	}
	_modifiable(modify, action);
	modify->_list.erase(modify->_list.begin() + start, modify->_list.begin() + start + count);
	return NativeInstanceListRef(modify, action);
}
NativeInstanceListRef NativeInstanceList::insert(InstanceParam value, Index before) {
	NativeInstanceList	*modify= NULL;
	RetainAction		action= exec::ReferenceCounted::Retain;
	
	if( (_list.size() == 0) && (-1 == before) ) {
		before= 0;
	}
	AssertMessageException( (_list.size() > 0) || (before == 0) );
	if(_list.size() > 0) {
		_validateAndFixIndex(before);
	}
	_modifiable(modify, action);
	modify->_list.insert(modify->_list.begin() + before, value);
	return NativeInstanceListRef(modify, action);
}
InstanceParam NativeInstanceList::operator[](Index index) const {
	return at(index);
}
NativeInstanceListRef NativeInstanceList::clear() {
	return remove(0, -1);
}
NativeInstanceListRef NativeInstanceList::append(InstanceParam value) {
	return insert(value, -1);
}
NativeInstanceListRef NativeInstanceList::push(InstanceParam value) {
	return insert(value, -1);
}
NativeInstanceListRef NativeInstanceList::pop(InstanceRef &value) {
	value= at(-1);
	return remove(-1, 1);
}
NativeInstanceList::~NativeInstanceList() {
}
void NativeInstanceList::_modifiable(NativeInstanceList *&modifiable, NativeInstanceList::RetainAction &action) {
	if(references() == 1) {
		modifiable= this;
		action= exec::ReferenceCounted::Retain;
	} else {
		modifiable= new NativeInstanceList(_list.size());
		modifiable->_list= _list;
		action= exec::ReferenceCounted::DoNotRetain;
	}
}
void NativeInstanceList::_validateAndFixIndex(Index &index) const {
	AssertMessageException(index >= -1 * static_cast<Index>(_list.size()));
	AssertMessageException(index < static_cast<Index>(_list.size()));
	if(index < 0) {
		index+= _list.size();
	}
}

#endif // __NativeInstanceList_h__
