#ifndef __gxInstances_h__
#define __gxInstances_h__

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include "os/ReferenceCounted.h"
#include "os/Exception.h"
#include "os/Mutex.h"

class Instance : public exec::ReferenceCounted {
	public:
		Instance(Instance *actualType);
		bool isa(Instance *actualType);
		bool does(Instance *behavior);
		Instance *createModifiableCopy();
		Instance *getType() const;
	protected:
		virtual ~Instance();
		virtual Instance *createClone()= 0;
	private:
		Instance	*_type;
		friend class TypeSystem;
};

class IntrinsicList;
typedef IntrinsicList	ExtrinsicInstance; ///< Extrinsics are just lists with

class IntrinsicInteger : public Instance {
	public:
		IntrinsicInteger(Instance *actualType, int64_t initialValue);
	protected:
		virtual ~IntrinsicInteger();
		virtual Instance *createClone();
	private:
		int64_t	_value;
};

class IntrinsicDouble : public Instance {
	public:
		IntrinsicDouble(Instance *actualType, double initialValue);
	protected:
		virtual ~IntrinsicDouble();
		virtual Instance *createClone();
	private:
		double	_value;
};

class IntrinsicList : public Instance {
	public:
		typedef std::vector<Instance*>	List;
		IntrinsicList(Instance *actualType);
		IntrinsicList(Instance *actualType, List::iterator begin, List::iterator end, RetainAction action= Retain);
		size_t count() const;
		/// Does not retain or release.
		Instance *get(size_t index);
		/// Does not retain or release. To grow this list, set the size() index.
		void set(size_t index, Instance *value);
	protected:
		virtual ~IntrinsicList();
		virtual Instance *createClone();
	private:
		List	_value;
};

class IntrinsicMap : public Instance {
	public:
		class HashableCompare {
			public:
				bool operator()(const Instance *x,const Instance *y); // returns x>y
		};
		typedef std::map<Instance*,Instance*,HashableCompare>	Map;
		IntrinsicMap(Instance *actualType);
		IntrinsicMap(Instance *actualType, Map::iterator begin, Map::iterator end, RetainAction action= Retain);
	protected:
		virtual ~IntrinsicMap();
		virtual Instance *createClone();
	private:
		Map	_value;
};

class IntrinsicBuffer : public Instance {
	public:
		/// Copies the data from buffer into it's own buffer
		IntrinsicBuffer(Instance *actualType, const void *buffer, size_t bytes);
		IntrinsicBuffer(Instance *actualType, const char *text);
		const void *data() const;
		size_t size() const;
		std::string &buffer();
	protected:
		virtual ~IntrinsicBuffer();
		virtual Instance *createClone();
	private:
		std::string	_value;
};

class IntrinsicReference : public Instance {
	public:
		IntrinsicReference(Instance *actualType, Instance *data);
		Instance *lock();
		void unlock(Instance *data);
	protected:
		virtual ~IntrinsicReference();
		virtual Instance *createClone();
	private:
		/** @note We may not need this class. I think createClone() handles this.
		*/
		class Reference : public Instance {
			public:
				Reference(Instance *data);
				Instance *get();
				void set(Instance *data);
			protected:
				virtual ~Reference();
				virtual Instance *createClone();
			private:
				Instance	*_value;
				exec::Mutex	_mutex;

		};
		Reference	*_valueReference;
};

/**
	@param actualType	In instance of type "type". Can be NULL in some rare circumstances.
							Gets retained.
*/
inline Instance::Instance(Instance *actualType):exec::ReferenceCounted(), _type(actualType) {
	if(NULL != actualType) {
		actualType->retain();
	}
}
inline bool Instance::isa(Instance *actualType) {ThrowMessageException("TODO: implement");}
inline bool Instance::does(Instance *behavior) {ThrowMessageException("TODO: implement");}
inline Instance *Instance::createModifiableCopy() {
	if(references() == 1) {
		retain();
		return this;
	}
	return createClone();
}
inline Instance *Instance::getType() const {return _type;}
inline Instance::~Instance() {}

/** @todo another constructor that doesn't take the type */
inline IntrinsicInteger::IntrinsicInteger(Instance *actualType, int64_t initialValue)
	:Instance(actualType), _value(initialValue) {}
inline IntrinsicInteger::~IntrinsicInteger() {}
inline Instance *IntrinsicInteger::createClone() {
	return new IntrinsicInteger(getType(), _value);
}

/** @todo another constructor that doesn't take the type */
inline IntrinsicDouble::IntrinsicDouble(Instance *actualType, double initialValue)
	:Instance(actualType), _value(initialValue) {}
inline IntrinsicDouble::~IntrinsicDouble() {}
inline Instance *IntrinsicDouble::createClone() {
	return new IntrinsicDouble(getType(), _value);
}

/**
	@note This is also an extrinsic. Use the constructor that takes the type for Extrnsics.
	@todo another constructor that doesn't take the type
*/
inline IntrinsicList::IntrinsicList(Instance *actualType):Instance(actualType), _value() {}
inline IntrinsicList::IntrinsicList(Instance *actualType, List::iterator begin, List::iterator end, RetainAction action)
		:Instance(actualType), _value(begin, end) {
	if(Retain == action) {
		for(List::iterator item= _value.begin(); item != _value.end(); ++item) {
			if(NULL != *item) {
				(*item)->retain();
			}
		}
	}
}
inline size_t IntrinsicList::count() const {return _value.size();}
inline Instance *IntrinsicList::get(size_t index) {return _value[index];}
inline void IntrinsicList::set(size_t index, Instance *value) {
	if(index == count()) {
		_value.push_back(value);
	} else {
		_value[index]= value;
	}
}
inline IntrinsicList::~IntrinsicList() {}
inline Instance *IntrinsicList::createClone() {
	return new IntrinsicList(getType(), _value.begin(), _value.end());
}

/** @todo another constructor that doesn't take the type */
inline IntrinsicMap::IntrinsicMap(Instance *actualType):Instance(actualType), _value() {}
inline IntrinsicMap::IntrinsicMap(Instance *actualType, Map::iterator begin, Map::iterator end, RetainAction action)
	:Instance(actualType), _value(begin, end) {
	if(Retain == action) {
		for(Map::iterator item= _value.begin(); item != _value.end(); ++item) {
			if(NULL != item->second) {
				item->second->retain();
			}
		}
	}
}
inline IntrinsicMap::~IntrinsicMap() {}
/** @todo retain top level contents */
inline Instance *IntrinsicMap::createClone() {
	return new IntrinsicMap(getType(), _value.begin(), _value.end());
}
inline bool IntrinsicMap::HashableCompare::operator()(const Instance *x,const Instance *y) {
	ThrowMessageException("TODO: implement"); // returns x>y
}

/** @todo another constructor that doesn't take the type */
inline IntrinsicBuffer::IntrinsicBuffer(Instance *actualType, const void *buffer, size_t bytes)
	:Instance(actualType), _value(reinterpret_cast<const char*>(buffer), bytes) {}
inline IntrinsicBuffer::IntrinsicBuffer(Instance *actualType, const char *text)
	:Instance(actualType), _value(text) {}
inline const void *IntrinsicBuffer::data() const {return _value.data();}
inline size_t IntrinsicBuffer::size() const {return _value.size();}
inline std::string &IntrinsicBuffer::buffer() {return _value;}
inline IntrinsicBuffer::~IntrinsicBuffer() {}
inline Instance *IntrinsicBuffer::createClone() {
	return new IntrinsicBuffer(getType(), data(), size());
}

/** @todo another constructor that doesn't take the type */
inline IntrinsicReference::IntrinsicReference(Instance *actualType, Instance *data)
		:Instance(actualType), _valueReference(new Reference(data)) {
	AssertMessageException(data != NULL);
}
/**
	@return	NULL means already locked
*/
inline Instance *IntrinsicReference::lock() {
	AssertMessageException(_valueReference->references() == 1);
	return _valueReference->get();
}
inline void IntrinsicReference::unlock(Instance *data) {
	AssertMessageException(_valueReference->references() == 1);
	_valueReference->set(data);
}
inline IntrinsicReference::~IntrinsicReference() {_valueReference->release();}
inline Instance *IntrinsicReference::createClone() {
	retain();
	return this;
}
inline IntrinsicReference::Reference::Reference(Instance *data)
		:Instance(NULL), _value(data), _mutex() {
	AssertMessageException(data != NULL);
}
inline Instance *IntrinsicReference::Reference::get() {
	exec::Mutex::Locker	lock(_mutex);
	Instance			*value= _value;

	_value= NULL;
	return value;
}
inline void IntrinsicReference::Reference::set(Instance *data) {
	exec::Mutex::Locker	lock(_mutex);

	AssertMessageException(_value == NULL);
	_value= data;
}
inline IntrinsicReference::Reference::~Reference() {}
inline Instance *IntrinsicReference::Reference::createClone() {
	ThrowMessageException("Should never be called.");
}

#endif // __gxInstances_h__
