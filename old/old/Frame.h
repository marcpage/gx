#ifndef __Frame_h__
#define __Frame_h__

#include "posix/MessageException.h"
#include "Block.h"
#include "BlockList.h"
#include <vector>
class ExecutionSystem;

class Frame {
	public:
		typedef NativeInstanceList::Index Index;
		Frame(Block *codeBlock, ExecutionSystem *preferredExecutionSystem= NULL);
		virtual ~Frame();
		void reset(Block *codeBlock, ExecutionSystem *preferredExecutionSystem= NULL);
		bool ready() const;
		void wireTo(Index output, Frame *frame, Index input);
		void start(BlockList *blocks);
		bool finished();
	private:
		struct WireRoute {
			Index	output;
			Frame	*frame;
			Index	input;
			WireRoute(Index o, Frame *f, Index i);
		};
		typedef std::vector<WireRoute>			WriteRouteList;
		typedef uint32_t						Count;
		Block					*_block;
		ExecutionSystem			*_preferredExec;
		WireRouteList			_wiring;
		Count					_waitingFor;
		Block::InstanceList		_inputs;
		Block::InstanceList		_outputs;
		bool					_outputsCopied;
		Frame(const Frame&); ///< Prevent usage
		Frame &operator=(const Frame&); ///< Prevent usage
};

inline WireRoute::WireRoute(Index o, Frame *f, Index i)
	:output(o), frame(f), input(i) {}

inline Frame::Frame(Block *codeBlock, ExecutionSystem *preferredExecutionSystem)
	:_preferredExec(preferredExecutionSystem), _block(codeBlock), _wiring(), _waitingFor(0), _inputs(NULL), _outputs(NULL), _outputsCopied(false) {
	ThrowMessageExceptionIfNULL(_block);
	_block->retain();
	try {
		_inputs= new Block::InstanceList(_block->inputs());
		_outputs= new Block::InstanceList(_block->outputs());
	} catch(const std::exception&) {
		delete _inputs;
		delete _outputs;
		throw;
	}
}
inline Frame::~Frame() {
	//ThrowMessageExceptionIfNULL(_block);
	if(NULL != _block) {
		_block->release();
	}
	delete _inputs;
	delete _outputs;
}
inline void Frame::reset(Block *codeBlock, ExecutionSystem *preferredExecutionSystem) {
	ThrowMessageExceptionIfNULL(_block);
	_block->release();
	_block= codeBlock;
	ThrowMessageExceptionIfNULL(_block);
	_block->retain();
	_preferredExec= preferredExecutionSystem;
	ThrowMessageExceptionIfNULL(_inputs);
	ThrowMessageExceptionIfNULL(_outputs);
	_inputs->clear();
	_inputs->resize(_blocks->inputs());
	_outputs->clear();
	_outputs->resize(_blocks->outputs());
}
inline bool Frame::ready() const {
	return 0 == _waitingFor;
}
inline void Frame::wireTo(Index output, Frame *frame, Index input) {
	ThrowMessageExceptionIfNULL(frame);
	_wiring.push_back(WireRoute(output, frame, input));
	++frame->_waitingFor;
}
inline void Frame::start() {
	ThrowMessageExceptionIfNULL(_block);
	_block->start(_inputs, _outputs);
}
inline bool Frame::finished() {
	if(_block->finished()) {
		if(!_outputsCopied) {
			_outputsCopied= true;
		}
		for(WireRouteList::iterator route= _wiring.begin(); route != _wiring.end(); ++route) {
			ThrowMessageExceptionIfNULL(route->frame);
			// mutex here!!
			route->frame->_inputs[route->input]= _outputs[route->output];
			--route->frame->_waitingFor;
		}
		return true;
	}
	return false;
}

#endif // __Frame_h__
