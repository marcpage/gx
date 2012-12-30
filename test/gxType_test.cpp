#include "gxType.h"
#include <string>
#include <stdio.h>

// clang++ -I. test/gxType_test.cpp -o /tmp/testType -Wall -Weffc++ -Wextra -Wshadow -Wwrite-strings

class Instance {
	public:
		Instance(const std::string &name):_name(name) {}
		~Instance() {}
		const std::string &getName() const {return _name;}
	private:
		std::string	_name;
		Instance(const Instance&); // prevent usage
		Instance &operator=(const Instance&); // prevent usage
};

struct BehaviorInfo {
	const char * const	behavior;
	const char * const	behaviors;
	const char * const	methods;
} Behaviors[]= {
	{"object",		NULL,
		"type=o@self:type@type;"
		"equals=o@self,v@object:equals@boolean;"
		"compare=o@self,v@object:comparison@integer;"
		"hash=o@self:hash@integer;"
		"type=o@self:type@type;"
	},
	{"display",		"object",
		"astext=d@self:display@text;"
	},
	{"number",		"display",
		"add=x@self,y@number:sum@number;"
		"subtract=x@self,y@number:difference@number;"
		"multiply=x@self,y@number:product@number;"
		"divideby=dividend@self,divisor@number:quotient@number;"
		"remainderof=dividend@self,divisor@number:remainder@number;"
		"division=dividend@self,divisor@number:quotient@number,remainder@number;"
		"inverse=x@self:inverse@number;"
		"magnitude=x@self:magnitude@number;"
		"raisedto=base@self,exponent@number:power@number;"
		"root=radicand@self,index@number:root@number;"
		"negate=x@self:negated@number;"
		"logarithm=x@self,base@number:log@number;"
		"isnegative=x@self:negative@boolean;"
		"islessthan=x@self,y@number:less@boolean;"
		"isgreaterthan=x@self,y@number:greater@boolean;"
		"islessthanorequal=x@self,y@number:less@boolean;"
		"isgreaterthanorequal=x@self,y@number:greater@boolean;"
		"equals=x@self,y@number:equals@boolean;"
		"near=x@self,y@number:near@boolean;"
		"within=x@self,y@number,delta@number:near@boolean;"
		"cosine=x@self:cosine@number;"
		"sine=x@self:sine@number;"
		"tangent=x@self:tangent@number;"
		"cotangent=x@self:cotangent@number;"
		"secant=x@self:secant@number;"
		"cosecant=x@self:cosecant@number;"
		"arcsine=x@self:arcsine@number;"
		"arcosine=x@self:arcosine@number;"
		"arctangent=x@self:arctangent@number;"
		"arccotangent=x@self:arccotangent@number;"
		"arcsecant=x@self:arcsecant@number;"
		"arccosecant=x@self:arccosecant@number;"
		"hyperboliccosine=x@self:hyperboliccosine@number;"
		"hyperbolicsine=x@self:hyperbolicsine@number;"
		"hyperbolictangent=x@self:hyperbolictangent@number;"
		"hyperboliccotangent=x@self:hyperboliccotangent@number;"
		"hyperbolicsecant=x@self:hyperbolicsecant@number;"
		"hyperboliccosecant=x@self:hyperboliccosecant@number;"
		"hyperbolicarcsine=x@self:hyperbolicarcsine@number;"
		"hyperbolicarcosine=x@self:hyperbolicarcosine@number;"
		"hyperbolicarctangent=x@self:hyperbolicarctangent@number;"
		"hyperbolicarccotangent=x@self:hyperbolicarccotangent@number;"
		"hyperbolicarcsecant=x@self:hyperbolicarcsecant@number;"
		"hyperbolicarccosecant=x@self:hyperbolicarccosecant@number;"
		"angle=x@self,y@number:radians@number;"
		"nearestinteger=x@self:int@integer;"
		"integernearestinfinity=x@self:int@integer;"
		"integernearestnegativeinfinity=x@self:int@integer;"
		"whole=x@self:int@integer;"
		"fraction=x@self:fraction@number;"
		"real=x@self:real@number;"
		"imaginary=x@self:i@number;"
	},
	{"integer",		"number",
		"shift=x@self,shiftleft@integer:shifted@integer;"
		"highestbit=x@self:highest@integer;"
		"lowestbit=x@self:lowest@integer;"
		"and=x@self,y@integer:masked@integer;"
		"or=x@self,y@integer:combined@integer;"
		"xor=x@self,y@integer:inverted@integer;"
		"not=x@self,bits@integer:inverted@integer;"
		"rotate=x@self,rotateleft@integer,bits@integer:rotated@integer;"
		"bitset=x@self,bit@integer:set@boolean;"
		"setbit=x@self,bit@integer,value@boolean:modified@integer;"
	},
	{"character",	"display",
		"ascii=c@self:value@integer;"
		"unicode=c@self:value@integer;"
	},
	{"buffer",		"object",
		"size=b@self:bytes@integer;"
		"getbyte=b@self,index@integer:byte@integer;"
		"sub=b@self,offset@integer,count@integer:sub@buffer;"
	},
	{"list",		"object",
		"fill=l@self,value@object,count@integer:filled@list;"
		"length=l@self:len@integer;"
		"append=l@self,o@object:appended@list;"
		"extend=l@self,o@list:extended@list;"
		"portion=l@self,offset@integer,count@integer:sub@list;"
		"remove=l@self,offset@integer,count@integer:smaller@list;"
		"insert=l@self,o@object,offset@integer:larger@list;"
		"inset=l@self,o@list,offset@integer:larger@list;"
		"find=l@self,o@object:position@integer;"
		"findat=l@self,o@object,offset@integer:position@integer;"
		"swap=l@self,index1@integer,index2@integer:result@list;"
		"reverse=l@self:reversed@list;"
		"rotate=l@self,rotateleft@integer:result@list;"
	},
	{"reference",	"object",
		"value=r@self:v@object;"
		"lock=r@self:r@reference,value@object;"
		"unlock=r@self,value@object:r@reference;"
	},
	{"type",		"display",
		"name=t@self:name@text;"
		"parent=t@self:parent@type;"
	},
	{"text",		"display",
		"at=t@self,position@integer:c@character;"
		"length=t@self:len@integer;"
		"portion=t@self,start@integer,count@integer:sub@text;"
		"find=t@self,sub@text:position@integer;"
		"findat=t@self,sub@text,start@integer:position@integer;"
		"lowercase=t@self:lower@text;"
		"uppercase=t@self:upper@text;"
		"startswith=t@self,prefix@text:starts@boolean;"
		"endswith=t@self,suffix@text:ends@boolean;"
		"split=t@self,firstcharacterofend@integer:front@text,end@text;"
		"strip=t@self:stripped@text;"
		"trim=t@self:trimmed@text;"
	},
	{"dictionary",	"object",
		"set=d@self,key@object,value@object:d@dictionary;"
		"get=d@self,key@object:v@object;"
		"delete=d@self,key@object:d@dictionary;"
		"has=d@self,key@object:has@boolean;"
	},
	{"boolean",		"display,object",
		"true=:true@boolean;"
		"false=:false@boolean;"
	},
};
int main(int, const char *[]) {
	type::Type::List		types;
	type::Behavior::List	behaviors;

	for(size_t index= 0; index < sizeof(Behaviors)/sizeof(Behaviors[0]); ++index) {
		behaviors.push_back(new type::Behavior(Behaviors[index].behavior));
	}
	for(size_t index= 0; index < sizeof(Behaviors)/sizeof(Behaviors[0]); ++index) {
		type::Behavior		*b= type::Behavior::lookup(Behaviors[index].behavior, behaviors);
		const char			*methods= Behaviors[index].methods;
		const char			*behaviorList= Behaviors[index].behaviors;

		while( (NULL != behaviorList) && ('\0' != *behaviorList) ) {
			const size_t	adjust= ','==*behaviorList ? 1 : 0;
			const char		*commaPos= strchr(behaviorList+adjust,',');
			const char		*endPos= NULL == commaPos ? &behaviorList[strlen(behaviorList)] : commaPos;
			std::string		name(behaviorList + adjust, endPos - behaviorList - adjust);
			type::Behavior	*related= type::Behavior::lookup(name, behaviors);

			b->addBehavior(related);
			behaviorList= endPos;
		}
		while('\0' != *methods) {
			const char		*equalsPos= strchr(methods, '=');
			std::string		methodName(methods, equalsPos - methods);
			type::Prototype	*p= new type::Prototype(methodName);
			const char		*parameter= equalsPos+1;

			while(':' != *parameter) {
				const size_t	adjust= (','==*parameter || ':'==*parameter) ? 1 : 0;
				const char		*atPos= strchr(parameter, '@');
				std::string		parameterName(parameter+adjust, atPos - parameter-adjust);
				const char		*typeStart= atPos+1;
				const char		*commaPos= strchr(typeStart, ',');
				const char		*colonPos= strchr(typeStart, ':');
				const char		*next= (NULL != commaPos) && (commaPos < colonPos) ? commaPos : colonPos;
				std::string		parameterType(typeStart, next - typeStart);
				const bool		isDispatch= "self"==parameterType;
				type::Behavior	*parameterBehavior= isDispatch ? b : type::Behavior::lookup(parameterType, behaviors);
				p->setInput(parameterName, parameterBehavior);
				if(isDispatch) {
					p->setDispatch(parameterName);
				}
				parameter= next;
			}
			while(';' != *parameter) {
				const size_t	adjust= (','==*parameter || ':'==*parameter) ? 1 : 0;
				const char	*atPos= strchr(parameter, '@');
				std::string	parameterName(parameter+adjust, atPos - parameter-adjust);
				const char	*typeStart= atPos+1;
				const char	*commaPos= strchr(typeStart, ',');
				const char	*semicolonPos= strchr(typeStart, ';');
				const char	*next= (NULL != commaPos) && (commaPos < semicolonPos) ? commaPos : semicolonPos;
				std::string	parameterType(typeStart, next - typeStart);
				p->setOutput(parameterName, type::Behavior::lookup(parameterType, behaviors));
				parameter= next;
			}
			b->addPrototype(p);
			methods= parameter + 1;
		}
	}
	for(size_t index= 0; index < behaviors.size(); ++index) {
		printf("%s [%d] %s",
			behaviors[index]->getName().c_str(),
			behaviors[index]->countMethods(),
			behaviors[index]->countBehaviors() == 0 ? "" : "related: "
		);
		for(size_t behaviorIndex= 0; behaviorIndex < behaviors[index]->countBehaviors(); ++behaviorIndex) {
			printf("%s ", behaviors[index]->getBehavior(behaviorIndex)->getName().c_str());
		}
		printf("\n");
		for(size_t methodIndex= 0; methodIndex < behaviors[index]->countMethods(); ++methodIndex) {
			type::Prototype	*p= behaviors[index]->getPrototype(methodIndex);
			const uint32_t	dispatch= p->getDispatch();

			printf("\t%s\n",p->getName().c_str());
			for(uint32_t param= 0; param < p->countInputs(); ++param) {
				printf("\t\t>%s(%s)%s\n",
					p->getInputName(param).c_str(),
					p->getInputType(param)->getName().c_str(),
					dispatch == param ? "dispatch" : ""
				);
			}
			for(uint32_t param= 0; param < p->countOutputs(); ++param) {
				printf("\t\t<%s(%s)\n",
					p->getOutputName(param).c_str(),
					p->getOutputType(param)->getName().c_str()
				);
			}
		}
	}
	return 0;
}
