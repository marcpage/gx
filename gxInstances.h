#ifndef __gxInstances_h__
#define __gxInstances_h__

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include "os/ExecutionReferenceCounted.h"
#include "os/MessageException.h"

class Instance : public exec::ReferenceCounted {
	public:
		Instance(Instance *actualType);
		bool is(Instance *actualType);
		bool does(Instance *behavior);
		Instance *modifiableCopy();
		Instance *type() const;
	protected:
		virtual ~Instance();
		virtual Instance *clone();
	private:
		Instance	*_type;
};

class ExtrinsicInstance : public Instance {
	public:
		ExtrinsicInstance(Instance *actualType);
	protected:
		virtual ~ExtrinsicInstance();
	private:
		std::vector<Instance*>	_members;
};

class IntrinsicInstance : public Instance {
	public:
		IntrinsicInstance(Instance *actualType);
	protected:
		virtual ~IntrinsicInstance();
};

class IntrinsicInteger64 : public IntrinsicInstance {
	public:
		IntrinsicInteger(Instance *actualType);
	protected:
		virtual ~IntrinsicInteger();
	private:
		int64_t	_value;
};

class IntrinsicDouble : public IntrinsicInstance {
	public:
		IntrinsicDouble(Instance *actualType);
	protected:
		virtual ~IntrinsicDouble();
	private:
		double	_value;
};

class IntrinsicList : public IntrinsicInstance {
	public:
		IntrinsicList(Instance *actualType);
	protected:
		virtual ~IntrinsicList();
	private:
		std::vector<Instance*>	_value;
};

class IntrinsicMap : public IntrinsicInstance {
	public:
		IntrinsicMap(Instance *actualType);
	protected:
		virtual ~IntrinsicMap();
	private:
		class HashableCompare {
			public:
				bool operator()(const Instance *x,const Instance *y); // returns x>y
		};
		std::map<Instance*,Instance*,HashableCompare>	_value;
};

class IntrinsicBuffer : public IntrinsicInstance {
	public:
		IntrinsicBuffer(Instance *actualType);
	protected:
		virtual ~IntrinsicBuffer();
	private:
		std::string	_value;
};

class IntrinsicReference : public IntrinsicInstance {
	public:
		IntrinsicReference(Instance *actualType);
	protected:
		virtual ~IntrinsicReference();
	private:
		Instance	*_valueReference;
};

inline Instance::Instance(Instance *actualType)
	:exec::ReferenceCounted(), _type(actualType) {}
inline bool Instance::is(Instance *actualType) {
	ThrowMessageException("TODO: implement");
}
inline bool Instance::does(Instance *behavior) {
	ThrowMessageException("TODO: implement");
}
inline Instance *Instance::modifiableCopy() {
	ThrowMessageException("TODO: implement");
}
inline Instance *Instance::type() const {
	return _type;
}
inline Instance::~Instance() {}
inline Instance *Instance::clone() {
	ThrowMessageException("TODO: implement");
}

#endif // __gxInstances_h__
