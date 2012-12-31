#ifndef __gxExecParameters_h__
#define __gxExecParameters_h__

#include <vector>
#include <stdint.h>

namespace gx {
	class Instance;
}

namespace exec {

	class Parameters {
		public:
			typedef std::vector<gx::Instance*>	InstanceList;
			Parameters();
			~Parameters();
			Parameters &setExpected(uint32_t count);
			uint32_t leftCount() const;
			gx::Instance *setParameter(uint32_t index, gx::Instance *value);
			gx::Instance *getParameter(uint32_t index);
			bool complete() const;
			Parameters &clear();
			bool empty() const;
			InstanceList &parameters();
		private:
			InstanceList	_parameters;
			uint32_t		_left;
	};


	inline Parameters::Parameters():_parameters(), _left(0) {}
	inline Parameters::~Parameters() {}
	inline Parameters &Parameters::setExpected(uint32_t count) {_left= count;}
	inline uint32_t Parameters::leftCount() const {return _left;}
	inline gx::Instance *Parameters::setParameter(uint32_t index, gx::Instance *value) {
		gx::Instance	*previousValue= NULL;

		while(_parameters.size() <= index) {
			_parameters.push_back(NULL);
		}
		previousValue= _parameters[index];
		_parameters[index]= value;
		if( (NULL == previousValue) && (NULL != value) && (_left > 0) ) {
			--_left;
		}
		return previousValue;
	}
	inline gx::Instance *Parameters::getParameter(uint32_t index) {
		if(index >= _parameters.size()) {return NULL;}
		return _parameters[index];
	}
	inline bool Parameters::complete() const {return _left= 0;}
	inline Parameters &Parameters::clear() {
		for(InstanceList::iterator i= _parameters.begin(); i != _parameters.end(); ++i) {
			*i= NULL;
		}
	}
	inline bool Parameters::empty() const {
		for(InstanceList::const_iterator i= _parameters.begin(); i != _parameters.end(); ++i) {
			if(NULL != *i) {
				return false;
			}
		}
		return true;
	}
	inline Parameters::InstanceList &Parameters::parameters() {return _parameters;}

}

#endif // __gxExecParameters_h__
