class Video {
	std::string id;
	std::string userid;
	std::string name;
	std::string chunks;

public:
	Video(std::string userid, std::string name){
		this->id = "0";
		this->userid = userid;
		this->name = name;
		this->chunks = "0";
	}

	Video() {};

	std::string getId() {
		return this->id;
	}

	void setId(std::string id) {
		this->id = id;
	}

	std::string getUserId() {
		return this->userid;
	}

	void setUserId(std::string userid) {
		this->userid = userid;
	}

	std::string getTitle() {
		return this->name;
	}

	void setTitle(std::string name) {
		this->name = name;
	}

	std::string getChunks() {
		return this->chunks;
	}

	void setChunks(std::string chunks) {
		this->chunks = chunks;
	}

	std::string getUrl() {
		return "uploads/user/" + this->getUserId() + "/video/" + this->getId() + "/";
	}

	std::string getPreview() {
		return this->getUrl() + "/preview.jpeg";
	}
};