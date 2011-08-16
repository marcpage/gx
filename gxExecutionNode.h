class ExecutionNode {
	public:
		Inputs();
		bool ready();
		bool set(int index, Reference &value);
	private:
		std::vector<Reference>	_inputs;
		int					_left;
};

class CompletionNode : public ExecutionNode {
	public:
		void route(int sourceIndex, ExecutionNode &destination, int sinkIndex);
	private:
		std::vector<pair<int, pair<ExecutionNode&,int> > >	_routing;
};

class Node : public ExecutionNode {
	public:
		CompletionNode &outputs();
	private:
		CompletionNode1	_outputs;
};

class Method : public Node {

};
