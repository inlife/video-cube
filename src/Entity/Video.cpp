class Video {
	std::string name;
	std::string preview;
	std::string authorId;
	std::string path;

public:
	Video(std::string path, std::string name, std::string id){
		this->name = name;
		this->preview = path + "\\preview.jpg";
		this->authorId = id;
	}

	std::string getName(){
		return this->name;
	}

};