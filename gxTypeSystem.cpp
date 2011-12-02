#include "gxTypeSystem.h"

// clang++ -c -I.. gxTypeSystem.cpp -o /tmp/gxTypeSystem.o -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings

static const char *typeName(TypeSystem::BasicTypes type) {
	switch(type) {
		case TypeSystem::tList:			return "gx.language.List";
		case TypeSystem::tMap:			return "gx.language.Map";
		case TypeSystem::tDouble:		return "gx.language.Double";
		case TypeSystem::tInteger64:	return "gx.language.Integer64";
		case TypeSystem::tBuffer:		return "gx.language.Buffer";
		case TypeSystem::tReference:	return "gx.language.Reference";
		case TypeSystem::tType:			return "gx.language.Type";
		case TypeSystem::tBehavior:		return "gx.language.Behavior";
		case TypeSystem::tDispatch:		return "gx.language.Dispatch";
		case TypeSystem::tInterface:	return "gx.language.Interface";
		case TypeSystem::tNativeMethod:	return "gx.language.NativeMethod";
		case TypeSystem::tMethod:		return "gx.language.Method";
		case TypeSystem::tCode:			return "gx.language.Code";
		case TypeSystem::tOrderedMap:	return "gx.language.OrderedMap";
		case TypeSystem::tASCIIText:	return "gx.language.ASCIIText";
		default:						break;
	};
	return NULL;
}

static const char *behaviorName(TypeSystem::BasicBehaviors behavior) {
	switch(behavior) {
		case TypeSystem::bNumber:		return "gx.language.Number";
		case TypeSystem::bInteger:		return "gx.language.Integer";
		case TypeSystem::bCharacter:	return "gx.language.Character";
		case TypeSystem::bBoolean:		return "gx.language.Boolean";
		case TypeSystem::bReal:			return "gx.language.Real";
		case TypeSystem::bText:			return "gx.language.Text";
		case TypeSystem::bBuffer:		return "gx.language.Buffer";
		case TypeSystem::bReference:	return "gx.language.Reference";
		case TypeSystem::bBehavior:		return "gx.language.Behavior";
		case TypeSystem::bType:			return "gx.language.Type";
		case TypeSystem::bInterface:	return "gx.language.Interface";
		case TypeSystem::bMethod:		return "gx.language.Method";
		case TypeSystem::bList:			return "gx.language.List";
		case TypeSystem::bMap:			return "gx.language.Map";
		case TypeSystem::bObject:		return "gx.language.Object";
		case TypeSystem::bDispatch:		return "gx.language.Dispatch";
		case TypeSystem::bHashable:		return "gx.language.Hashable";
		case TypeSystem::bDisplayable:	return "gx.language.Displayable";
		case TypeSystem::bSerializable:	return "gx.language.Serializable";
		case TypeSystem::bComparable:	return "gx.language.Comparable";
		case TypeSystem::bOrderedMap:	return "gx.language.OrderedMap";
		default:						break;
	};
	return NULL;
}

TypeSystem::TypeSystem()
		:_types(), _behaviors() {
	_startTypeInit();
	_startBehaviorInit();
	// at this point Types don't have dispatches, constants or members
	//	and Behaviors don't have methods
	_initTypeInstanceMembers();
}

void TypeSystem::_initTypeInstanceMembers() {
	struct NamedBehavior {
		const char * const	name;
		BasicBehaviors		behavior;
	};
	const NamedBehavior kMembersType[]= {
		{"Name", bText},
		{"Parent", bType},
		{"Dispatches", bList},
		{"Constants", bOrderedMap},
		{"Members", bOrderedMap},
	};
	const NamedBehavior kMembersBehavior[]= {
		{"Name", bText},
		{"Methods", bOrderedMap},
	};
	const NamedBehavior kMembersDispatch[]= {
		{"Behavior", bBehavior},
		{"Methods", bOrderedMap},
	};
	const NamedBehavior kMembersInterface[]= {
		{"Name", bText},
		{"Inputs", bOrderedMap},
		{"Outputs", bOrderedMap},
	};
	const NamedBehavior kMembersMethod[]= {
		{"Name", bText},
		{"Interface", bInterface},
	};
	const NamedBehavior kMembersNativeMethod[]= {
		{"Function", bInteger},
	};
	const NamedBehavior kMembersCode[]= {
		{"Code", bBuffer},
	};
	const NamedBehavior kMembersOrderedMap[]= {
		{"Names", bList},
		{"Values", bList},
	};
	const NamedBehavior kMembersASCIIText[]= {
		{"Buffer", bBuffer},
	};
	const struct {
		BasicTypes			type;
		const NamedBehavior	*members;
		size_t				count;
	} kTypeInstanceMembers[]= {
		{tType, &kMembersType[0], sizeof(kMembersType)/sizeof(kMembersType[0])},
		{tBehavior, &kMembersBehavior[0], sizeof(kMembersBehavior)/sizeof(kMembersBehavior[0])},
		{tDispatch, &kMembersDispatch[0], sizeof(kMembersDispatch)/sizeof(kMembersDispatch[0])},
		{tInterface, &kMembersInterface[0], sizeof(kMembersInterface)/sizeof(kMembersInterface[0])},
		{tMethod, &kMembersMethod[0], sizeof(kMembersMethod)/sizeof(kMembersMethod[0])},
		{tNativeMethod, &kMembersNativeMethod[0], sizeof(kMembersNativeMethod)/sizeof(kMembersNativeMethod[0])},
		{tCode, &kMembersCode[0], sizeof(kMembersCode)/sizeof(kMembersCode[0])},
		{tOrderedMap, &kMembersOrderedMap[0], sizeof(kMembersOrderedMap)/sizeof(kMembersOrderedMap[0])},
		{tASCIIText, &kMembersASCIIText[0], sizeof(kMembersASCIIText)/sizeof(kMembersASCIIText[0])},
	};
	for(unsigned int typeIndex= 0; typeIndex < sizeof(kTypeInstanceMembers)/sizeof(kTypeInstanceMembers[0]); ++typeIndex) {
		const char * const	theTypeName= typeName(kTypeInstanceMembers[typeIndex].type);
		ExtrinsicInstance	*type= dynamic_cast<ExtrinsicInstance*>(_types[theTypeName]);
		IntrinsicList		*names= dynamic_cast<IntrinsicList*>(type->get(0));

		for(unsigned int memberIndex= 0; memberIndex < kTypeInstanceMembers[typeIndex].count; ++memberIndex) {
			Instance	*behavior= getBehavior(kTypeInstanceMembers[typeIndex].members[memberIndex].behavior);

			behavior->retain(); // we did a get, not a create or new, so we need to retain
			names->set(memberIndex, _createText(kTypeInstanceMembers[typeIndex].members[memberIndex].name));
			names->set(memberIndex, behavior);
		}
	}
}

void TypeSystem::_startBehaviorInit() {
	Instance	*behaviorType= getType(tBehavior);
	Instance	*listType= getType(tList);

	// allocate all behaviors
	for(int behavior= 0; behavior < static_cast<int>(BehaviorCount); ++behavior) {
		const char * const	theBehaviorName= behaviorName(static_cast<BasicBehaviors>(behavior));
		IntrinsicList		*methodList= new IntrinsicList(listType);
		ExtrinsicInstance	*theBehavior= new ExtrinsicInstance(behaviorType);

		_behaviors[behaviorName(static_cast<BasicBehaviors>(behavior))]= theBehavior;
		theBehavior->set(0, _createText(theBehaviorName));	// Behavior field 0: name
		theBehavior->set(1, methodList);					// Behavior field 1: methods
	}
}

Instance *TypeSystem::_lookupParent(BasicTypes type) {
	if( (tCode == type) || (tNativeMethod == type) ) {
		return getType(tMethod);
	}
	return NULL;
}

ExtrinsicInstance *TypeSystem::_createText(const char * const text) {
	IntrinsicBuffer		*nameBuffer= new IntrinsicBuffer(getType(tBuffer), text);
	ExtrinsicInstance	*name= new ExtrinsicInstance(getType(tASCIIText));

	name->set(0, nameBuffer);		// ASCIIText field 0: buffer
	return name;
}

void TypeSystem::_startTypeInit() {
	Instance	*typeType; // The "type" type
	Instance	*orderedMapType;
	Instance	*listType;

	// allocate all types
	for(int type= 0; type < static_cast<int>(TypeCount); ++type) {
		_types[typeName(static_cast<BasicTypes>(type))]= new ExtrinsicInstance(NULL);
	}
	typeType= getType(tType);
	orderedMapType= getType(tOrderedMap);
	listType= getType(tList);
	for(int type= 0; type < TypeCount; ++type) {
		BasicTypes			asType= static_cast<BasicTypes>(type);
		const char * const	theTypeName= typeName(asType);
		ExtrinsicInstance	*theType= dynamic_cast<ExtrinsicInstance*>(_types[theTypeName]);
		Instance			*parent= _lookupParent(asType);
		IntrinsicList		*dispatchList= new ExtrinsicInstance(listType);
		ExtrinsicInstance	*constantsList= new ExtrinsicInstance(orderedMapType);
		ExtrinsicInstance	*membersList= new ExtrinsicInstance(orderedMapType);

		_types[theTypeName]->_type= typeType;
		theType->set(0, _createText(theTypeName));	// Type field 0: name
		theType->set(1, parent);					// Type field 1: parent type
		theType->set(2, dispatchList);				// Type field 2: list of Dispatches
		theType->set(3, constantsList);				// Type field 3: list of Constants
		theType->set(4, membersList);				// Type field 4: list of members of an instance
		constantsList->set(0, new IntrinsicList(listType));	// OrderedMap field 0: name list
		constantsList->set(1, new IntrinsicList(listType));	// OrderedMap field 1: value(value) list
		membersList->set(0, new IntrinsicList(listType));	// OrderedMap field 0: name list
		membersList->set(1, new IntrinsicList(listType));	// OrderedMap field 1: value(behavior) list

	}
}

TypeSystem::~TypeSystem() {
	for(Map::iterator type= _types.begin(); type != _types.end(); ++type) {
		//AssertMessageException((*type)->second != NULL);
		//AssertMessageException((*type)->second->references() == 1);
		type->second->release();
		type->second= NULL;
	}
	for(Map::iterator behavior= _behaviors.begin(); behavior != _behaviors.end(); ++behavior) {
		//AssertMessageException((*behavior)->second != NULL);
		//AssertMessageException((*behavior)->second->references() == 1);
		behavior->second->release();
		behavior->second= NULL;
	}
}

Instance *TypeSystem::getType(const char *name) {
	if(NULL == name) {
		return NULL;
	}
	Map::iterator	found= _types.find(name);

	if(found == _types.end()) {
		return NULL;
	}
	return found->second;
}

Instance *TypeSystem::getType(BasicTypes type) {
	return getType(typeName(type));
}

Instance *TypeSystem::getBehavior(const char *name) {
	if(NULL == name) {
		return NULL;
	}
	Map::iterator	found= _behaviors.find(name);

	if(found == _behaviors.end()) {
		return NULL;
	}
	return found->second;
}

Instance *TypeSystem::getBehavior(BasicBehaviors behavior) {
	return getBehavior(behaviorName(behavior));
}

void TypeSystem::add(Instance * /*type*/) {
	ThrowMessageException("TODO: Implement");
}
