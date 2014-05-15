class VideoRepository : public Cooper::EntityRepository {
public: 
	std::vector<Video> getByUserId(std::string id) {
		std::vector<Video> videos;

		return videos;
	}
	/*
	Video create(std::string userId, std::string name){
		//Video video = Video(createVideoFolder(userId, name), name, userId);
		return Video();	
	}

	std::string createVideoFolder(std::string usetId){
		std::string folder;

		//Folder is created in windows standart. Replace it with Unix standart
		folder = "users\\" + userId + "\\" + name;

		const char _dirPath[] = folder.c_str();
		boost::filesystem::path dir(_dirPath);
		return folder;
		return std::string();
	}*/
};