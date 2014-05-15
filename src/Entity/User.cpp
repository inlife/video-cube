class User {
	std::string id;
	std::string login;
	std::string password;

public:
	User(std::string name, std::string password) {
		this->id = "0";
		this->login = login;
		this->password = password;		
	}

	User() {
		this->id = "0";
	}

	std::string getId() {
		return this->id;
	}

	void setId(std::string id) {
		this->id = id;
	}

	std::string getLogin() {
		return this->login;
	}

	void setLogin(std::string login) {
		this->login = login;
	}

	std::string getPassword() {
		return this->password;
	}

	void setPassword(std::string password) {
		this->password = password;
	}

	std::vector<Video> getUserVideos() {
		VideoRepository vr = VideoRepository();

		return vr.getByUserId(this->id);
	}
};