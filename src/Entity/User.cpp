class User {
	std::string id;
	std::string name;
	std::string password;

public:
	User(std::string name, std::string password) {
		this->id = "1";
		this->name = name;
		this->password = password;		
	}

	std::string getName() {
		return this->name;
	}

	std::string getPassword() {
		return this->password;
	}
};