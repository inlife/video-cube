namespace Cooper {

	namespace Http {

		class ParameterBag {
			std::map <std::string, std::string> data;
		public:

			bool exists(std::string name) {
				return ((this->data.count(name) != 0) && this->data[name].size() > 0);
			}

			std::string get(std::string name) {
				if (this->exists(name)) {
					return this->data[name];
				}
				return std::string();
			}

			std::string operator[] (std::string name) {
				return this->get(name);
			}

			void set(std::string name, std::string value) {
				this->data[name] = value;
			}

			void add(std::string name, std::string value) {
				this->set(name, value);
			}

			ParameterBag() {};
		};	
	}
}