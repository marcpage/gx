class Instance;

class InstanceReference {
	public:
		enum RetainAction {
			Retain,
			DoNotRetain
		};
		InstanceReference(Instance *actualInstance, RetainAction action);
		~InstanceReference();
		template<typename T> T *instance();
	private:
		Instance	*_instance;
};

class Number : public InstanceReference {
	public:
		Number(Instance *actualInstance, RetainAction action);
		virtual ~Number();
};

class Integer : public Number {
	public:
		static Integer integer64(int64_t value);
		Integer(Instance *actualInstance, RetainAction action);
		virtual ~Integer();
};


class Real : public Number {
	public:
		static Real double64(double value);
		Real(Instance *actualInstance, RetainAction action);
		virtual ~Real();
};

class Text : public InstanceReference {
	public:
		static Text ascii(const char *string);
		static Text ascii(void *buffer, size_t size);
		const Integer &length();
		const Integer &character(const Integer &index);
		Text(Instance *actualInstance, RetainAction action);
		virtual ~Text();
};

class List : public InstanceReference {
	public:
		List(Instance *actualInstance, RetainAction action);
		virtual ~List();
};

class Map : public InstanceReference {
	public:
		Map(Instance *actualInstance, RetainAction action);
		virtual ~Map();
};

class Buffer : public InstanceReference {
	public:
		Buffer(const void *address, size_t size);
		Buffer(Instance *actualInstance, RetainAction action);
		virtual ~Buffer();
};

class Reference : public InstanceReference {
	public:
		Reference(Instance *value);
		Reference(Instance *actualInstance, RetainAction action);
		virtual ~Reference();
};

class Type : public InstanceReference {
	public:
		Type(Instance *actualInstance, RetainAction action);
		virtual ~Type();
};

class Behavior : public InstanceReference {
	public:
		Behavior(Instance *actualInstance, RetainAction action);
		virtual ~Behavior();
};

class Interface : public InstanceReferences {
	public:
		Interface(Instance *actualInstance, RetainAction action);
		virtual ~Interface();
};

class Method : public InstanceReferences {
	public:
		static Method code(const Test &name, const Buffer &instructions);
		static Method native(const Test &name, void *function); ///< @todo change void* to correct prototype
		Method(Instance *actualInstance, RetainAction action);
		virtual ~Method();
		void call(const std::vector<Instance*> &inputs, std::vector<Instance*> &outputs); ///< @todo correct
};