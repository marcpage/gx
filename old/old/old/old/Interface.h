#ifndef _Interface_h_
#define _Interface_h_

#include "ReferenceCounted.h"
#include "ForwardDeclares.h"
#include <vector>

class Interface : public ReferenceCounted {
	public:
		typedef InterfacePtr	Ptr;
		static Ptr create(StringParam name);
		Interface &addInput(StringParam name, BehaviorParam behavior);
		Interface &addOutput(StringParam name, BehaviorParam behavior);
		size_t findInput(StringParam name) const;
		size_t findOutput(StringParam name) const;
		StringParam inputName(size_t index) const;
		StringParam outputName(size_t index) const;
	protected:
		Interface();
		Interface(StringParam theName);
		Interface(const Interface &other);
		Interface &operator=(const Interface &other);
	private:
		typedef std::vector<SmartPtr<Named<Behavior> > >	NamedBehaviorList;
		StringPtr			_name;
		NamedBehaviorList	_inputs;
		NamedBehaviorList	_outputs;
		virtual ~Interface();
};

#endif // _Interface_h_
