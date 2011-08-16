#ifndef __Engine_h__
#define __Engine_h__

#include "posix/ExecutionQueue.h"
#include "posix/ExecutionThread.h"
#include "Block.h"
#include "Frame.h"

class Engine : public exec::Thread {
	public:
		Engine();
		virtual ~Engine();
		Frame *createFrame(Block *codeBlock);
		void recyleFrame(Frame *discard);
		void schedule(Frame *ready);
	protected:
		virtual void *run();
	private:
		exec::Queue<Frame*>	_available;
		exec::Queue<Frame*>	_scheduled;
};

inline Engine::Engine()
		:exec::Thread(), _available(), _scheduled() {
	start();
}
inline Engine::~Engine() {
}
inline Frame *Engine::createFrame(Block *codeBlock, ExecutionSystem *preferredExecutionSystem= NULL) {
	Frame	*found= NULL;
	const double	secondsToWaitForUnusedBlock= 0.0001; // 100 us
	
	if(_available.dequeue(&found, secondsToWaitForUnusedBlock)) {
		found->reset(codeBlock, preferredExecutionSystem);
	} else {
		found= new Frame(codeBlock, preferredExecutionSystem);
	}
	return found;
}
inline void Engine::recyleFrame(Frame *discard) {
	_available.enqueue(&discard);
}
inline void Engine::schedule(Frame *ready) {
	_scheduled.enqueue(ready);
}
inline void *Engine::run() {
	TODO Fill In
}

#endif // __Engine_h__
