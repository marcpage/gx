#ifndef __gxType_h__
#define __gxType_h__

#include <string>
#include <vector>
#include <stdint.h>

class Instance;

namespace type {

	class Type;
	class Behavior;
	class Prototype;
	typedef std::vector<Instance*>				InstanceList;
	template<typename T>
	class NamedItem : std::pair<std::string,T*> {
		public:
			NamedItem():std::pair<std::string,T*>() {}
			NamedItem(const std::string &name, T *value):std::pair<std::string,T*>(name, value) {}
			NamedItem(const NamedItem &other):std::pair<std::string,T*>(other) {}
			~NamedItem() {}
			NamedItem &operator=(const NamedItem &other) {first= other.first; second= other.second;}
			const std::string &getName() const {return first;}
			NamedItem *operator->() {return this;}
	};
	class Dispatch : std::pair<Behavior*,InstanceList> {
		public:
			Dispatch():std::std::pair<Behavior*,InstanceList>() {}
			Dispatch(const std::string &name):std::std::pair<Behavior*,InstanceList>(name, InstanceList()) {}
			Dispatch(const Dispatch &other):std::std::pair<Behavior*,InstanceList>(other) {}
			~Dispatch() {}
			Dispatch &operator=(const Dispatch &other) {first= other.first; second= other.second;}
			const std::string &getName() const {return first->getName();}
			Dispatch *operator->() {return this;}
	};
	typedef std::vector<Behavior*>				BehaviorList;
	typedef std::vector<Type*>					TypeList;
	typedef std::NamedItem<Type>				NamedType;
	typedef std::vector<NamedType>				NamedTypeList;
	typedef std::NamedItem<Instance>			NamedInstance;
	typedef std::vector<NamedInstance>			NamedInstanceList;
	typedef std::vector<Dispatch*>				DispatchList;
	typedef std::vector<Prototype*>				PrototypeList;
	class Prototype {
		public:
			Prototype(const std::string &name);
			~Prototype();
			const std::string &getName() const;
			Prototype &setInput(const std::string &name, Type *parameterType);
			Prototype &setOutput(const std::string &name, Type *parameterType);
			uint32_t lookupInput(const std::string &name);
			uint32_t lookupOutput(const std::string &name);
			uint32_t countInputs();
			uint32_t countOutputs();
			Type *getInputType(uint32_t parameter);
			Type *getOutputType(uint32_t parameter);
		private:
			std::string		_name;
			NamedTypeList	_inputs;
			NamedTypeList	_outputs;
	};
	class Behavior {
		public:
			static Behavior *lookup(const std::string &name, const BehaviorList &behaviors);
			Behavior(const std::string &name, Behavior *parent);
			~Behavior();
			const std::string &getName() const;
			Behavior &addPrototype(Prototype *prototype);
			uint32_t lookupPrototype(const std::string &name);
			uint32_t countPrototypes();
			Prototype *getPrototype(uint32_t prototypeId);
		private:
			std::string			_name;
			Behavior			*_parent;
			PrototypeList		_prototypes;
	};
	class Type {
		public:
			static Type *lookup(const std::string &name, const TypeList &types);
			Type(const std::string &name, Type *parent);
			~Type();
			const std::string &getName() const;
			Type &setMember(const std::string &name, Type *memberType);
			Type &setConstant(const std::string &name, Instance *value);
			Type &setMethod(Behavior *behavior, const std::string &methodName, Instance *method);
			uint32_t lookupMember(const std::string &name);
			uint32_t lookupConstant(const std::string &name);
			uint32_t lookupBehavior(const std::string &name);
			uint32_t lookupMethod(uint32_t behavior, const std::string &name);
			uint32_t countMembers();
			uint32_t countConstants();
			uint32_t countBehaviors();
			uint32_t countMethods(uint32_t behavior);
			Type *getMemberType(uint32_t memberId);
			Instance *getConstant(uint32_t constantId);
			Instance *getMethod(uint32_t behavior, uint32_t method);
		private:
			std::string			_name;
			Type				*_parent;
			NamedTypeList		_members;
			NamedInstanceList	_constants;
			DispatchList		_dispatch;
	};

	inline template<typename LIST>
	uint32_t _findItemInNamedList(const std::string &name, const LIST &list) {
		for(LIST::iterator item= list.begin(); item != list.end(); ++item) {
			if((*item)->getName() == name) {
				return item - list.begin();
			}
		}
		return static_cast<uint32_t>(-1);
	}
	inline template<typename LIST, typename VALUE>
	void _setItemInNamedList(const std::string &name, VALUE *value, LIST &list) {
		uint32_t	index= _findItemInNamedList(name, list);

		if(index == static_cast<uint32_t>(-1)) {
			list.push_back(LIST::value_type(name, value));
		} else {
			list[index].second= value;
		}
	}
	inline template<typename LIST>
	inline LIST::value_type *_lookup(const std::string &name, const LIST &list) {
		for(LIST::iterator item= list.begin(); item != list.end(); ++item) {
			if(name == (*item)->getName()) {
				return &*item;
			}
		}
		return NULL;
	}

	inline Prototype::Prototype(const std::string &name)
			:_name(name), _inputs(), _outputs() {}
	inline Prototype::~Prototype() {}
	inline const std::string &Prototype::getName() const {return _name;}
	inline Prototype &Prototype::setInput(const std::string &name, Type *parameterType) {
		_setItemInNamedList(name, parameterType, _inputs);
		return *this;
	}
	inline Prototype &Prototype::setOutput(const std::string &name, Type *parameterType) {
		_setItemInNamedList(name, parameterType, _outputs);
		return *this;
	}
	inline uint32_t Prototype::lookupInput(const std::string &name) {
		return _findItemInNamedList(name, _inputs);
	}
	inline uint32_t Prototype::lookupOutput(const std::string &name) {
		return _findItemInNamedList(name, _outputs);
	}
	inline uint32_t Prototype::countInputs() {return _inputs.size();}
	inline uint32_t Prototype::countOutputs() {return _outputs.size();}
	inline Type *Prototype::getInputType(uint32_t parameter) {return _inputs[parameter].second;}
	inline Type *Prototype::getOutputType(uint32_t parameter) {return _outputs[parameter].second;}

	inline Behavior *Behavior::lookup(const std::string &name, const BehaviorList &behaviors) {
		return _lookup(name, behaviors);
	}
	inline Behavior::Behavior(const std::string &name, Behavior *parent)
			:_name(name), _parent(parent), _prototypes() {}
	inline Behavior::~Behavior() {}
	inline const std::string &Behavior::getName() const {return _name;}
	inline Behavior &Behavior::addPrototype(Prototype *prototype) {_prototypes.push_back(prototype);}
	inline uint32_t Behavior::lookupPrototype(const std::string &name) {
		return _findItemInNamedList(name, _prototypes);
	}
	inline uint32_t Behavior::countPrototypes() {return _prototypes.size();}
	inline Prototype *Behavior::getPrototype(uint32_t prototypeId) {return _prototypes[prototypeId];}

			std::string			_name;
			Type				*_parent;
			NamedTypeList		_members;
			NamedInstanceList	_constants;
			DispatchList		_dispatch;
	inline Type *Type::lookup(const std::string &name, const TypeList &types) {
		return _lookup(name, types);
	}
	inline Type::Type(const std::string &name, Type *parent)
			:_name(name), _parent(parent), _members(), _constants(), _dispatch() {}
	inline Type::~Type() {}
	inline const std::string &Type::getName() const {return _name;}
	inline Type &Type::setMember(const std::string &name, Type *memberType) {
		_setItemInNamedList(name, memberType, _members);
		return *this;
	}
	inline Type &Type::setConstant(const std::string &name, Instance *value) {
		_setItemInNamedList(name, memberType, _constants);
		return *this;
	}
	inline Type &Type::setMethod(Behavior *behavior, const std::string &methodName, Instance *method) {
		uint32_t	behaviorId= _findItemInNamedList(behavior->getName(), _dispatch);
	uint32_t _findItemInNamedList(const std::string &name, const LIST &list) {
	uint32_t _setItemInNamedList(const std::string &name, VALUE *value, LIST &list) {

	}
	inline uint32_t Type::lookupMember(const std::string &name) {
	}
	inline uint32_t Type::lookupConstant(const std::string &name) {
	}
	inline uint32_t Type::lookupBehavior(const std::string &name) {
	}
	inline uint32_t Type::lookupMethod(uint32_t behavior, const std::string &name) {
	}
	inline uint32_t Type::countMembers() {
	}
	inline uint32_t Type::countConstants() {
	}
	inline uint32_t Type::countBehaviors() {
	}
	inline uint32_t Type::countMethods(uint32_t behavior) {
	}
	inline Type *Type::getMemberType(uint32_t memberId) {
	}
	inline Instance *Type::getConstant(uint32_t constantId) {
	}
	inline Instance *Type::getMethod(uint32_t behavior, uint32_t method) {
	}

}

#endif // __gxType_h__
