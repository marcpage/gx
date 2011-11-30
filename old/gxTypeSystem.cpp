#include "gxTypeSystem.h"
#include "gxIntrinsicASCIIText.h"
#include "gxIntrinsicInterface.h"
#include "gxIntrinsicType.h"
#include "gxText.h"

namespace gx {

	#define kAverageMinimumTypes		50 ///< Optimisation
	#define kAverageMinimumInterfaces	50 ///< Optimisation
	TypeSystem::TypeSystem()
		:_types(kAverageMinimumTypes), _interfaces(kAverageMinimumInterfaces) {
		IntrinsicType	*object, *type, *asciiText;
		enum Strings {
			sObject,
			sType,
			sInterface,
			sText,
			sASCIIText,
			sMethod,
			sPrototype,
			sNativeInteger,
			sNativeReal,
			sBuffer,
			sList,
			sReference,
			StringCount
		};
		enum Kind {
			kInterface,
			kType,
			kInterfaceAndType
		};
		struct {
			Strings				kind;
			const char * const	value;
			Kind				where;
		} stringInits[]= {
			{sObject,		"gx.Object",	kInterfaceAndType},
			{sInterface,	"gx.Interface",	kInterfaceAndType},
			{sType,			"gx.Type",		kInterfaceAndType},
			{sText,			"gx.Text",		kInterface},
			{sASCIIText,	"gx.ASCIIText",	kType},
			{sMethod,		"gx.Method",	kInterface},
			{sPrototype,	"gx.Prototype",	kInterfaceAndType},
		};
		Text		stringList[StringCount];
		Interface	interfaceList[StringCount];
		Type		typeList[StringCount];

		compileTimeAssert(sizeof(stringInits)/sizeof(stringInits[0]) == StringCount);
		type= new IntrinsicType(Text(), Type(), Type());
		type->_type.assign(type, Pointer::Retain);
		object= new IntrinsicType(Text(), type, Type()); // parent is supposed to be NULL
		type->_parent.assign(object, Pointer::Retain);
		asciiText= new IntrinsicType(Text(), type, object);
		typeList[sObject].assign(object, Pointer::DoNotRetain);
		typeList[sType].assign(type, Pointer::DoNotRetain);
		typeList[sASCIIText].assign(asciiText, Pointer::DoNotRetain);
		
		for(size_t index= 0; index < StringCount; ++index) {
			stringList[stringInits[index].kind].assign(
				new IntrinsicASCIIText(asciiText, stringInits[index].value, -1, NULL),
				Pointer::DoNotRetain
			);
		}
		for(size_t index= 0; index < StringCount; ++index) {
			if( (!typeList[stringInits[index].kind].vaid())
					&& (stringInits[index].where == kType)
						|| (stringInits[index].where == kInterfaceAndType) ) {
				typeList[stringInits[index].kind].assign(
					new IntrinsicType(stringList[stringInits[index].kind], typeList[sType], typeList[sObject]),
					Pointer::DoNotRetain
				);
			}
		}
		for(size_t index= 0; index < StringCount; ++index) {
			if( (stringInits[index].where == kInterface)
					|| (stringInits[index].where == kInterfaceAndType) ) {
				interfaceList[stringInits[index].kind].assign(
					new IntrinsicInterface(stringList[stringInits[index].kind], typeList[sInterface]),
					Pointer::DoNotRetain
				);
			}
		}
		for(size_t index= 0; index < StringCount; ++index) {
			if(stringInits[index].where == kInterfaceAndType) {
				typeList[stringInits[index].kind].add(interfaceList[stringInits[index].kind]);
			}
		}
		for(size_t index= 0; index < StringCount; ++index) {
			// fill internal type and interface tables
		}
	}
	TypeSystem::~TypeSystem() {
	}
	TypeSystem &TypeSystem::add(const Type &aType) {
		_types.push_back(aType);
		return  *this;
	}
	TypeSystem &TypeSystem::add(const Interface &anInterface) {
		_interfaces.push_back(anInterface);
		return *this;
	}
	bool TypeSystem::get(const Text &name, Type &theType) const {
		for(TypeList::const_iterator m= _types.begin(); m != _types.end(); ++m) {
			if(m->ref<IntrinsicType>().name().equals(name)) {
				theType= *m;
				return true;
			}
		}
		return false;
	}
	bool TypeSystem::get(const Text &name, Interface &theInterface) const {
		for(InterfaceList::const_iterator m= _interfaces.begin(); m != _interfaces.end(); ++m) {
			if(m->ref<IntrinsicInterface>().name().equals(name)) {
				theInterface= *m;
				return true;
			}
		}
		return false;
	}
	void TypeSystem::remove(const Type &theType) {
		ThrowMessageException("TODO: Implement");
	}
	void TypeSystem::remove(const Interface &theInterface) {
		ThrowMessageException("TODO: Implement");
	}
} // namespace gx
