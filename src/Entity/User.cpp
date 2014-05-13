class User {
	std::string id;
	std::string name;
	std::string password;

public:
	User(std::string name, std::string password) {
		this->id = "0";
		this->name = name;
		this->password = password;		
	}

	User() {
		this->id = "0";
	}

	std::string getName() {
		return this->name;
	}

	std::string getPassword() {
		return this->password;
	}

	std::vector<Video> getUserVideos() {
		VideoRepository vr = VideoRepository();

		return vr.getByUserId(this->id);
	}
};