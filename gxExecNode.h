#ifndef __gxExecNode_h__
#define __gxExecNode_h__

#include "gxExecParameters.h"
#include "gxMethod.h"
#include <stdint.h>

namespace exec {

	class Queue;

	class Node {
		public:
			Node();
			~Node();
			void setMethod(gx::Method *method);
			Node &addRoute(uint32_t output, Parameters &input, uint23_t index);
			Parameters &getInputs();
			Parameters &getOutputs();
			bool ready() const;
			bool done() const;
			void start(Queue *queue);
			void route();
		private:
			struct RouteElement {
				uint32_t	sourceIndex;
				Parameters	*sink;
				uint32_t	sinkIndex;
				RouteElement(uint32_t srcIdx, Parameters &snk, uint32_t snkIdx)
						:sourceIndex(srcIdx), sink(&snk), sinkIndex(snkIdx) {}
			};
			typedef std::vector<RouteElement>	RouteTable;
			gx::Method	*_method;
			Parameters	_inputs;
			Parameters	_outputs;
			RouteTable	_route;
			Node(const Node &o); // Prevent Usage
			Node &operator=(const Node &o); // Prevent Usage
	};

	inline Node::Node()
		:_method(NULL), _inputs(), _outputs(),_route() {}
	inline Node::~Node() {}
	inline void Node::setMethod(gx::Method *method) {_method= method;}
	inline Node &Node::addRoute(uint32_t output, Parameters &input, uint23_t index) {
		_route.push_back(RouteElement(output, input, index));
	}
	inline Parameters &Node::getInputs() {return _inputs;}
	inline Parameters &Node::getOutputs() {return _outputs;}
	inline bool Node::ready() const {return _inputs.complete();}
	inline bool Node::done() const {return _outputs.complete();}
	inline void Node::start(Queue *queue) {
		_method->start(queue, _inputs.parameters(), _outputs.parameters);
	}
	inline void Node::route() {
		Parameters::InstanceList	&source= _outputs.parameters();
		std::vector<bool>			retainNeeded(source.size());

		for(RouteTable::iterator path= _route.begin(); path != _route.end(); ++path) {
			Instance	*oldInput;

			oldInput= path->sink->setParameter(path->sinkIndex, source[path->sourceIndex]);
			// assert(NULL == oldInput);
			if(retainNeeded[path->sourceIndex]) {
				source[path->sourceIndex]->retain();
			} else {
				retainNeeded[path->sourceIndex]= true;
			}
		}
		for(size_t sourceIndex= 0; sourceIndex < sourceIndex.size(); ++sourceIndex) {
			if(!retainNeeded[sourceIndex] && (NULL != source[sourceIndex])) {
				source[sourceIndex]->release(); // unused output
			}
			source[sourceIndex]= NULL;
		}
	}

}

#endif // __gxExecNode_h__
