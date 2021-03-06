#ifndef __gxType_h__
#define __gxType_h__

#include <string>
#include <vector>
#include <stdint.h>
#include "gxUtilities.h"

namespace gx {
	class Instance;
}

namespace type {

	class Type;
	class Behavior;
	class Prototype;
	typedef std::vector<gx::Instance*>		InstanceList;
	template<typename T>
	class Named {
		public:
			typedef std::vector<Named<T> >	List;
			Named():first(),second(NULL) {}
			Named(const std::string &name, T *value):first(name), second(value) {}
			Named(const Named &other):first(other.first), second(other.second) {}
			~Named() {}
			Named &operator=(const Named &other) {
				this->first= other.first; this->second= other.second;
				return *this;
			}
			const std::string &getName() const {return this->first;}
			Named *operator->() {return this;}
			const Named *operator->() const {return this;}
		public:
			std::string	first;
			T			*second;
	};
	class Prototype {
		public:
			typedef std::vector<Prototype*>	List;
			Prototype(const std::string &name);
			~Prototype();
			bool operator==(const Prototype &other);
			bool operator!=(const Prototype &other);
			const std::string &getName() const;
			uint32_t setDispatch(const std::string &name);
			Behavior *setInput(const std::string &name, Behavior *parameterType);
			Behavior *setOutput(const std::string &name, Behavior *parameterType);
			uint32_t lookupInput(const std::string &name);
			uint32_t lookupOutput(const std::string &name);
			uint32_t countInputs();
			uint32_t countOutputs();
			Behavior *getInputType(uint32_t parameter);
			Behavior *getOutputType(uint32_t parameter);
			const std::string &getInputName(uint32_t parameter);
			const std::string &getOutputName(uint32_t parameter);
			uint32_t getDispatch();
		private:
			std::string				_name;
			Named<Behavior>::List	_inputs;
			Named<Behavior>::List	_outputs;
			uint32_t				_dispatch;
	};
	class Behavior {
		public:
			typedef std::vector<Behavior*>	List;
			static Behavior *lookup(const std::string &name, const List &behaviors);
			Behavior(const std::string &name);
			~Behavior();
			const std::string &getName() const;
			Behavior &addBehavior(Behavior *behavior);
			Behavior &addPrototype(Prototype *prototype);
			uint32_t lookupBehavior(const std::string &name);
			uint32_t lookupMethod(const std::string &name);
			uint32_t countBehaviors();
			uint32_t countMethods();
			Behavior *getBehavior(uint32_t behaviorId);
			Prototype *getPrototype(uint32_t methodId);
		private:
			std::string			_name;
			List				_behaviors;
			Prototype::List		_prototypes;
			Behavior(const Behavior&); // prevent usage
			Behavior &operator=(const Behavior&); // prevent usage
	};
	class Dispatch {
		public:
			typedef std::vector<Dispatch>	List;
			Dispatch():first(NULL), second() {}
			Dispatch(Behavior *behavior):first(behavior), second() {}
			Dispatch(const Dispatch &other):first(other.first), second(other.second) {}
			~Dispatch() {}
			Dispatch &operator=(const Dispatch &other) {
				this->first= other.first; this->second= other.second;
				return *this;
			}
			const std::string &getName() const {return this->first->getName();}
			Dispatch *operator->() {return this;}
			const Dispatch *operator->() const {return this;}
		public:
			Behavior		*first;
			InstanceList	second;
	};
	class Type {
		public:
			typedef std::vector<Type*>	List;
			static Type *lookup(const std::string &name, const List &types);
			Type(const std::string &name, Type *parent);
			~Type();
			const std::string &getName() const;
			Behavior *setMember(const std::string &name, Behavior *memberType);
			gx::Instance *setConstant(const std::string &name, gx::Instance *value);
			gx::Instance *setMethod(Behavior *behavior, const std::string &methodName, gx::Instance *method);
			uint32_t lookupMember(const std::string &name);
			uint32_t lookupConstant(const std::string &name);
			uint32_t lookupBehavior(const std::string &name);
			uint32_t lookupMethod(uint32_t behavior, const std::string &name);
			uint32_t countMembers();
			uint32_t countConstants();
			uint32_t countBehaviors();
			uint32_t countMethods(uint32_t behaviorId);
			Behavior *getMemberBehavior(uint32_t memberId);
			gx::Instance *getConstant(uint32_t constantId);
			Behavior *getBehavior(uint32_t behaviorId);
			gx::Instance *getMethod(uint32_t behaviorId, uint32_t method);
			const std::string &getMemberName(uint32_t memberId) const;
			const std::string &getConstantName(uint32_t constantId) const;
			Type *getParent();
		private:
			std::string					_name;
			Type						*_parent;
			Named<Behavior>::List		_members;
			Named<gx::Instance>::List	_constants;
			Dispatch::List				_dispatch;
			Type(const Type&); // prevent usage
			Type &operator=(const Type&); // prevent usage
	};

	template<typename LIST>
	uint32_t _findItemInNamedList(const std::string &name, const LIST &list) {
		for(typename LIST::const_iterator item= list.begin(); item != list.end(); ++item) {
			if(util::equalsIgnoreCase((*item)->getName(), name)) {
				return item - list.begin();
			}
		}
		return static_cast<uint32_t>(-1);
	}
	template<typename LIST, typename VALUE>
	VALUE *_setItemInNamedList(const std::string &name, VALUE *value, LIST &list) {
		uint32_t	index= _findItemInNamedList(name, list);
		VALUE		*original= NULL;

		if(index == static_cast<uint32_t>(-1)) {
			typedef typename LIST::value_type	LISTvalue_type;
			list.push_back(LISTvalue_type(name, value));
		} else {
			original= list[index].second;
			list[index].second= value;
		}
		return original
	}
	template<typename LIST>
	typename LIST::value_type _lookup(const std::string &name, const LIST &list) {
		for(typename LIST::const_iterator item= list.begin(); item != list.end(); ++item) {
			if(util::equalsIgnoreCase((*item)->getName(), name)) {
				return *item;
			}
		}
		return NULL;
	}

	inline Prototype::Prototype(const std::string &name)
			:_name(name), _inputs(), _outputs(), _dispatch(static_cast<uint32_t>(-1)) {}
	inline Prototype::~Prototype() {}
	inline bool operator==(const Prototype &other) {
		if( (_dispatch != other._dispatch)
				|| (name.size() != other.name.size())
				|| (_inputs.size() != other._inputs.size())
				|| (_outputs.size() != other._outputs.size()) ){
			return false;
		}
		if
	}
	inline bool operator!=(const Prototype &other) {return !(*this == other);}
	inline const std::string &Prototype::getName() const {return _name;}
	inline Prototype &Prototype::setDispatch(const std::string &name) {
		return util::assignAndReturnOriginal(_dispatch, lookupInput(name));
	}
	inline Behavior *Prototype::setInput(const std::string &name, Behavior *parameterType) {
		return _setItemInNamedList(name, parameterType, _inputs);
	}
	inline Prototype &Prototype::setOutput(const std::string &name, Behavior *parameterType) {
		return _setItemInNamedList(name, parameterType, _outputs);
	}
	inline uint32_t Prototype::lookupInput(const std::string &name) {
		return _findItemInNamedList(name, _inputs);
	}
	inline uint32_t Prototype::lookupOutput(const std::string &name) {
		return _findItemInNamedList(name, _outputs);
	}
	inline uint32_t Prototype::countInputs() {return _inputs.size();}
	inline uint32_t Prototype::countOutputs() {return _outputs.size();}
	inline Behavior *Prototype::getInputType(uint32_t parameter) {return _inputs[parameter].second;}
	inline Behavior *Prototype::getOutputType(uint32_t parameter) {return _outputs[parameter].second;}
	inline const std::string &Prototype::getInputName(uint32_t parameter) {
		return _inputs[parameter].first;
	}
	inline const std::string &Prototype::getOutputName(uint32_t parameter) {
		return _outputs[parameter].first;
	}
	inline uint32_t Prototype::getDispatch() {return _dispatch;}

	inline Behavior *Behavior::lookup(const std::string &name, const List &behaviors) {
		return _lookup(name, behaviors);
	}
	inline Behavior::Behavior(const std::string &name)
			:_name(name), _behaviors(), _prototypes() {}
	inline Behavior::~Behavior() {}
	inline const std::string &Behavior::getName() const {return _name;}
	inline Behavior &Behavior::addBehavior(Behavior *behavior) {
		_behaviors.push_back(behavior);
		for(uint32_t index= 0; index < behavior->countMethods(); ++index) {
			const std::string	&name= behavior->getPrototype(index)->getName();
			uint32_t			prototypeId= _findItemInNamedList(name, _prototypes);

			if(static_cast<uint32_t>(-1) == prototypeId) {
				_prototypes.push_back(behavior->getPrototype(index));
			}
		}
		return *this;
	}
	inline Behavior &Behavior::addPrototype(Prototype *prototype) {
		_prototypes.push_back(prototype);
		return *this;
	}
	inline uint32_t Behavior::lookupBehavior(const std::string &name) {
		return _findItemInNamedList(name, _behaviors);
	}
	inline uint32_t Behavior::lookupMethod(const std::string &name) {
		return _findItemInNamedList(name, _prototypes);
	}
	inline uint32_t Behavior::countBehaviors() {
		return _behaviors.size();
	}
	inline uint32_t Behavior::countMethods() {
		return _prototypes.size();
	}
	inline Behavior *Behavior::getBehavior(uint32_t behaviorId) {
		return _behaviors[behaviorId];
	}
	inline Prototype *Behavior::getPrototype(uint32_t prototypeId) {
		return _prototypes[prototypeId];
	}

	inline Type *Type::lookup(const std::string &name, const List &types) {
		return _lookup(name, types);
	}
	inline Type::Type(const std::string &name, Type *parent)
			:_name(name), _parent(parent), _members(), _constants(), _dispatch() {}
	inline Type::~Type() {}
	inline const std::string &Type::getName() const {return _name;}
	inline Behavior *Type::setMember(const std::string &name, Behavior *memberType) {
		return _setItemInNamedList(name, memberType, _members);
	}
	inline gx::Instance *Type::setConstant(const std::string &name, gx::Instance *value) {
		return _setItemInNamedList(name, value, _constants);
	}
	inline gx::Instance *Type::setMethod(Behavior *behavior, const std::string &methodName, gx::Instance *method) {
		uint32_t		behaviorId= _findItemInNamedList(behavior->getName(), _dispatch);
		uint32_t		methodId;
		gx::Instance	*oldMethod= NULL;

		if(static_cast<uint32_t>(-1) == behaviorId) {
			behaviorId= _dispatch.size();
			_dispatch.push_back(Dispatch(behavior));
		}
		for(uint32_t index= 0; index < behavior->countBehaviors(); ++index) {
			Behavior	*related= behavior->getBehavior(index);

			methodId= related->lookupMethod(methodName);
			if(static_cast<uint32_t>(-1) != methodId) {
				setMethod(related, methodName, method);
			}
		}
		methodId= _dispatch[behaviorId].first->lookupMethod(methodName);
		// assert(methodId != static_cast<uint32_t>(-1))
		while(methodId >= _dispatch[behaviorId]->second.size()) {
			_dispatch[behaviorId]->second.push_back(NULL);
		}
		oldMethod= _dispatch[behavior].second[methodId];
		_dispatch[behaviorId]->second[methodId]= method;
		return oldMethod;
	}
	inline uint32_t Type::lookupMember(const std::string &name) {
		uint32_t	memberIndex= _findItemInNamedList(name, _members);

		if(static_cast<uint32_t>(-1) == memberIndex) {
			return (NULL == _parent ? NULL : _parent->lookupMember(name));
		}
		return (NULL == _parent ? 0 : _parent->countMembers()) + memberIndex;
	}
	inline uint32_t Type::lookupConstant(const std::string &name) {
		uint32_t	constantIndex= _findItemInNamedList(name, _constants);

		if(static_cast<uint32_t>(-1) == constantIndex) {
			return (NULL == _parent ? NULL : _parent->lookupConstant(name));
		}
		return (NULL == _parent ? 0 : _parent->countConstants()) + constantIndex;
	}
	inline uint32_t Type::lookupBehavior(const std::string &name) {
		return _findItemInNamedList(name, _dispatch);
	}
	inline uint32_t Type::lookupMethod(uint32_t behavior, const std::string &name) {
		return _dispatch[behavior].first->lookupMethod(name);
	}
	inline uint32_t Type::countMembers() {
		return (NULL == _parent ? 0 : _parent->countMembers()) + _members.size();
	}
	inline uint32_t Type::countConstants() {
		return (NULL == _parent ? 0 : _parent->countConstants()) + _constants.size();
	}
	inline uint32_t Type::countBehaviors() {return _dispatch.size();}
	inline uint32_t Type::countMethods(uint32_t behaviorId) {
		return _dispatch[behaviorId].first->countMethods();
	}
	inline Behavior *Type::getMemberBehavior(uint32_t memberId) {
		uint32_t	ancestorMembers= (NULL == _parent ? 0 : _parent->countMembers());

		if(memberId >= ancestorMembers) {
			return _members[memberId - ancestorMembers].second;
		}
		//assert(NULL != _parent)
		return (NULL == _parent ? NULL : _parent->getMemberBehavior(memberId));
	}
	inline gx::Instance *Type::getConstant(uint32_t constantId) {
		uint32_t	ancestorConstants= (NULL == _parent ? 0 : _parent->countConstants());

		if(constantId >= ancestorConstants) {
			return _constants[constantId - ancestorConstants].second;
		}
		//assert(NULL != _parent)
		return (NULL == _parent ? NULL : _parent->getConstant(constantId));
	}
	inline Behavior *Type::getBehavior(uint32_t behaviorId) {
		return _dispatch[behaviorId].first;
	}
	inline gx::Instance *Type::getMethod(uint32_t behaviorId, uint32_t method) {
		return _dispatch[behaviorId]->second[method];
	}
	inline const std::string &Type::getMemberName(uint32_t memberId) const {
		uint32_t	ancestorMembers= (NULL == _parent ? 0 : _parent->countMembers());

		if(memberId >= ancestorMembers) {
			return _members[memberId - ancestorMembers].first;
		}
		//assert(NULL != _parent)
		return _parent->getMemberName(memberId);
	}
	inline const std::string &Type::getConstantName(uint32_t constantId) const {
		uint32_t	ancestorConstants= (NULL == _parent ? 0 : _parent->countConstants());

		if(constantId >= ancestorConstants) {
			return _constants[constantId - ancestorConstants].first;
		}
		//assert(NULL != _parent)
		return _parent->getConstantName(constantId);
	}
	inline Type *Type::getParent() {return _parent;}
	}

}

#endif // __gxType_h__
