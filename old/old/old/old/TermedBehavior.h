#ifndef _TermedBehavior_h_
#define _TermedBehavior_h_

#include "Behavior.h"
#include <vector>

class TermedBehavior : public Behavior {
	public:
		typedef std::vector<Ptr>	BehaviorList;
		Ptr create(const String &name);
		TermedBehavior &add(const String &termName);
		TermedBehavior &add(const String &termName, const Ptr &theType);
		TermedBehavior &set(const Ptr &parent);
		Ptr specific(const BehaviorList &types);
		size_t term(const String &name);
		Ptr placeholder(const String &name);
	protected:
		TermedBehavior();
		TermedBehavior(const String &name);
		TermedBehavior(const String &name, TermedBehaviorParam parent);
		TermedBehavior(const TermedBehavior &other);
		TermedBehavior &operator=(const TermedBehavior &other);
	private:
		typedef std::vector<Ptr>	BehaviorList;
		NamedInterfaceList	_terms;
		BehaviorList		_placeholders;
		virtual ~TermedBehavior();
};

#endif // _TermedBehavior_h_
