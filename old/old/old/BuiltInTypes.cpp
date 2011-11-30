#include "BuiltInTypes.h"
#include "Instance.h"
#include "NativeString.h"
#include "NativeInstanceList.h"
#include "posix/MessageException.h"
#include "NativeInstance.h"

// g++ -c -o /tmp/BuiltInTypes.o BuiltInTypes.cpp -I.. -g -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings

/** 
	@todo fill in behaviors
	@todo fill in constants
	@todo fill in dispatches
*/
ExecutionAtomicInitialize;
static const InstanceReference<NativeInstance>::RetainAction DoNotRetainNativeInstance
												= InstanceReference<NativeInstance>::DoNotRetain;
static const InstanceReference<Instance>::RetainAction DoNotRetainInstance
												= InstanceReference<Instance>::DoNotRetain;
static const int	typeMemberCount= 6;
NativeInstanceRef	*builtInTypes= NULL;

void initBuiltInTypes() {
	struct MemberInfo {
		const char *	name;
		BuiltInTypes	type;
	};
	MemberInfo	noMembers[]= {
		{NULL, NumberOfBuiltInTypes},
	};
	MemberInfo	behaviorMembers[]= {
		{"name", tNativeString},
		{"methods", tNativeInstanceList},
		{NULL, NumberOfBuiltInTypes},
	};
	MemberInfo	namedTypeMembers[]= {
		{"name", tNativeString},
		{"type", tType},
		{NULL, NumberOfBuiltInTypes},
	};
	MemberInfo	methodMembers[]= {
		{"name", tNativeString},
		{"inputs", tNativeInstanceList},
		{"outputs", tNativeInstanceList},
		{NULL, NumberOfBuiltInTypes},
	};
	MemberInfo	typeMembers[]= {
		{"name", tNativeString},
		{"parent", tType},
		{"behaviors", tNativeInstanceList},
		{"members", tNativeInstanceList},
		{"constants", tNativeInstanceList},
		{"dispatches", tNativeInstanceList},
		{NULL, NumberOfBuiltInTypes},
	};
	MemberInfo	dispatchMembers[]= {
		{"behavior", tBehavior},
		{"methods", tNativeInstanceList},
	};
	struct {
		BuiltInTypes type;
		BuiltInTypes parent;
		const char *name;
		MemberInfo *members;
	} builtInTypeInitInfo[NumberOfBuiltInTypes]= {
		{tNativeInteger,		tObject,				"gx.native.integer",	noMembers},
		{tNativeMethod,			tObject,				"gx.native.method",		noMembers},
		{tNativeString,			tObject,				"gx.native.string",		noMembers},
		{tNativeInstanceList,	tObject,				"gx.native.list",		noMembers},
		{tObject,				NumberOfBuiltInTypes,	"gx.object",			noMembers},
		{tBehavior,				tObject,				"gx.behavior",			behaviorMembers},
		{tNamedType,			tObject,				"gx.namedtype",			namedTypeMembers},
		{tMethod,				tObject,				"gx.method",			methodMembers},
		{tDispatchTable,		tObject,				"gx.dispatchtable",		dispatchMembers},
		{tType,					tObject,				"gx.type",				typeMembers},
	};
	AssertMessageException(NumberOfBuiltInTypes == sizeof(builtInTypeInitInfo)/sizeof(builtInTypeInitInfo[0]));
	builtInTypes= new NativeInstanceRef[NumberOfBuiltInTypes];
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		builtInTypes[type].assign(new NativeInstance(typeMemberCount), 0, DoNotRetainNativeInstance);
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		AssertMessageException(builtInTypes[type]->references() == 1);
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		builtInTypes[type]->_type= builtInTypes[tType];
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		int	memberCount= 0;
		
		for(memberCount= 0; builtInTypeInitInfo[type].members[memberCount].name != NULL; ++memberCount) {
		}
		NativeInstanceList	*memberTypes= new NativeInstanceList(memberCount);

		for(int member= 0; member < memberCount; ++member) {
			memberTypes->append(InstanceRef());
		}
		// set member list (empty types)
		builtInTypes[type]->_members[3].assign(memberTypes, 0, DoNotRetainInstance);
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		builtInTypes[type]->member(0, // type name
			InstanceRef(new NativeString(builtInTypeInitInfo[type].name), DoNotRetainInstance)
		);
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		if(NumberOfBuiltInTypes != builtInTypeInitInfo[type].parent) {
			typecastFast(builtInTypes[builtInTypeInitInfo[type].parent], builtInTypes[type]->member(1));
		}
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		for(int member= 0; builtInTypeInitInfo[type].members[member].name != NULL; ++member) {
			NativeInstance	*memberInstance= new NativeInstance(builtInTypes[tNamedType]);
			memberInstance->_members[0].assign(new NativeString(builtInTypeInitInfo[type].members[member].name), 0, DoNotRetainInstance);
			typecastFast(builtInTypes[builtInTypeInitInfo[type].members[member].type], memberInstance->_members[1]);
			InstanceRef	memberList= builtInTypes[type]->_members[3];
			AssertMessageException(memberList->type() == builtInTypes[tNativeInstanceList]);
			NativeInstanceList	*memberListPtr= reinterpret_cast<NativeInstanceList*>(memberList.operator->());
			memberListPtr->_list[member].assign(memberInstance, 0, DoNotRetainInstance);
		}
	}
	for(int type= 0; type < NumberOfBuiltInTypes; ++type) {
		AssertMessageException(static_cast<int>(builtInTypes[type]->_members.size()) == typeMemberCount);
	}
}
void cleanupBuiltInTypes() {
	exec::AtomicNumber::cleanup();
}
