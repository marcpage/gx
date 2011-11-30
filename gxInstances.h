#ifndef __gxInstances_h__
#define __gxInstances_h__

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include "posix/ExecutionReferenceCounted.h"
#include "gxBehaviors.h"

class Instance : public exec::ReferenceCounted {
	public:
		Instance(const Type &actualType);
		bool is(const Type &actualType);
		bool does(const Interface &interface);
		template<typename T> T* modifiableCopy();
		const Type &type() const;
	protected:
		virtual ~Instance();
		virtual Instance *clone();
	private:
		Type	_type;
};

class ExtrinsicInstance : public Instance {
	public:
		ExtrinsicInstance();
	protected:
		virtual ~ExtrinsicInstance();
	private:
		std::vector<Instance*>	_members;
};

class IntrinsicInstance : public Instance {
	public:
		IntrinsicInstance();
	protected:
		virtual ~IntrinsicInstance();
};

class IntrinsicInteger64 : public IntrinsicInstance {
	public:
		IntrinsicInteger();
	protected:
		virtual ~IntrinsicInteger();
	private:
		int64_t	_value;
};

class IntrinsicDouble : public IntrinsicInstance {
	public:
		IntrinsicDouble();
	protected:
		virtual ~IntrinsicDouble();
	private:
		double	_value;
};

class IntrinsicList : public IntrinsicInstance {
	public:
		IntrinsicList();
	protected:
		virtual ~IntrinsicList();
	private:
		std::vector<Instance*>	_value;
};

class IntrinsicMap : public IntrinsicInstance {
	public:
		IntrinsicMap();
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
		IntrinsicBuffer();
	protected:
		virtual ~IntrinsicBuffer();
	private:
		std::string	_value;
};

class IntrinsicReference : public IntrinsicInstance {
	public:
		IntrinsicReference();
	protected:
		virtual ~IntrinsicReference();
	private:
		Instance	*_value;
};

#endif // __gxInstances_h__
