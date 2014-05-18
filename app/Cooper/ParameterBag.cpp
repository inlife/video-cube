namespace Cooper {

	// Class to store any type of params
	class ParameterBag {
		std::map <std::string, std::string> data;
	public:

		// Check element for existance and emptyness
		bool exists(std::string name) {
			return ((this->data.count(name) != 0) && this->data[name].size() > 0);
		}

		// Data getter
		std::string get(std::string name) {
			if (this->exists(name)) {
				return this->data[name];
			}
			return std::string();
		}

		// Data[] getter
		std::string operator[] (std::string name) {
			return this->get(name);
		}

		// Data setter
		void set(std::string name, std::string value) {
			this->data[name] = value;
		}

		// Data setter
		void add(std::string name, std::string value) {
			this->set(name, value);
		}
		
		ParameterBag() {};
	};	
}