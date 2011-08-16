class Scheduler {
	public:
		Scheduler();
		~Scheduler();
		typedef IDType 		*BlockID;
		typedef uint32_t	Index;
		BlockID add(CodeBlockPtr code);
		void map(BlockID sourceBlock, Index output, BlockID syncBlock, Index input);
		void ready(BlockID block); ///< inputs and outputs are mapped
		bool step();
		void complete(BlockID block);
	private:
		enum State {
			Added,
			Ready,
			Running,
			Complete
		}
		struct BlockParameter {
			BlockID	block;
			Index	index;
			BlockParameter(BlockID blockID, Index paramIndex);
			BlockParameter(const BlockParameter &other);
			BlockParameter &operator=(const BlockParameter &other);
		};
		struct Route {
			BlockParameter	source;
			BlockParameter	sync;
			Route(BlockID sourceBlock, Index output, BlockID syncBlock, Index input);
		};
		struct Frame {
			State			state;
			CodeBlockPtr	code;
			InstanceListPtr	inputs;
			InstanceListPtr	outputs;
			Frame(CodeBlockPtr codeBlock);
			Frame(const Frame &other);
			Frame &operator=(const Frame &other);
			void reset(CodeBlockPtr codeBlock);
		};
	typedef std::vector<Frame>	FrameList;
	typedef std::vector<Route>	SignalList;
	FrameList				_frames;
	SignalList				_signals;
	FrameList::size_type	_nextBlockID; ///< if completed block is less, becomes completed block id
	FrameList::size_type _reserveBlockID(); ///< looks for next block id
};

BlockID Scheduler::add(CodeBlockPtr code) {
	FrameList::size_type	index= _reserveBlockID();
	
	ASERT(index <= _frames.size());
	if(index == _frames.size()) {
		_frames.push_back(Frame(code));
	} else {
		_frames[index].reset(code);
	}
}
void Scheduler::map(BlockID sourceBlock, Index output, BlockID syncBlock, Index input) {
	_signals.push_back(Route(sourceBlock, output, syncBlock, input));
}
void Scheduler::ready(BlockID block) {
	_frames[block].state= Ready;
}
bool Scheduler::step() {
	FrameList::size_type	tailComplete= 0;
	
	for(FrameList::size_type blockID= 0; blockID < _frames.size(); ++blockID) {
		bool	ranSomething= false;
		
		if(Ready == _frames[blockID].state) {
			_frames[blockID].state= Running;
			_frames[blockID].code->run(this, blockID, inputs, outputs);
			ranSomething= true;
		}
		if(Complete == _frames[blockID].state) {
			SignalList::size_type	signalIndex= 0;
			
			while(signalIndex < _signals.size()) {
				const BlockParameter	&source= _signals[signalIndex].source;
				const BlockParameter	&sync= _signals[signalIndex].sync;
				
				if(source.block == blockID)  {
					_frames[sync.block].inputs.assign(sync.index, _frames[source.block].outputs.get(source.index));
					_signals.erase(_signals.begin() + signalIndex);
				} else {
					++signalIndex;
				}
				++tailComplete;
			}
			if(blockID < _nextBlockID) {
				_nextBlockID= blockID;
			}
		} else {
			tailComplete= 0;
		}
		if(ranSomething) {
			return true;
		}
	}
	if(tailComplete > 0) { // erase any tail complete items
		_frames.erase(_frames.begin() + _frames.size() - tailComplete, _frames.end());
	}
	return false;
}
void Scheduler::complete(BlockID block) {
	_frames[block].state= Complete;
}
BlockID Scheduler::_reserveBlockID() {
	BlockID	reserved= _nextBlockID;
	
	while( (_nextBlockID < _frames.size()) && (Complete != _frames[_nextBlockID].state) ) {
		++_nextBlockID;
	}
	if(_nextBlockID == reserved) {
		++_nextBlockID;
	}
	return reserved;
}
