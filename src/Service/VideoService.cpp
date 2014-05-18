class VideoService {
public:

	Video getPlayerVideo() {
		Cooper::ParameterBag data = Cooper::Http::get();
		
		VideoRepository vr;
		
		if (data.exists("id") && vr.exists(data.get("id"))) {

			return vr.load(data.get("id"));

		} else {
			throw Cooper::Exceptions::FormException("Video doesn't exist");
		}
	}

	void upload(User user) {
		cgicc::Cgicc cgi;

		cgicc::form_iterator ptitle = cgi.getElement("title");
		cgicc::const_file_iterator file = cgi.getFile("file");

		if (!ptitle->isEmpty() && ptitle != (*cgi).end() && file != cgi.getFiles().end()) {

			if (file->getDataType() != "video/mp4") 
				throw Cooper::Exceptions::FormException("Video must be in mp4 format.");

			std::string title = **ptitle;
			std::ofstream myfile;
			myfile.open("uploads/tmp/" + file->getFilename());

			file->writeToStream(myfile);

			VideoRepository vr;

			// TODO: add video to database
			Video video = vr.create(user.getId(), title);

			// TODO: generate folder structure
			std::string path = this->generateFolders(
				video.getUserId(), video.getId()
			);

			// TODO: execute conversion
			int _chunks = Encoder::convertVideo(
				10, "uploads/tmp/" + file->getFilename(), path
			);
			std::string chunks =  boost::lexical_cast<std::string>(_chunks);
			
			// TODO: update video in database
			video.setChunks(chunks);
			vr.updateChunks(video);

			// TODO: remove video from tmp
			this->removeTmp("uploads/tmp/" + file->getFilename());

			std::cout << "Content-type: text/html\r\n\r\n";
			std::cout << video.getId();

		} else {
			throw Cooper::Exceptions::FormException("Please, fill in all fields."); 
		}
	}

	void removeTmp(std::string name) {
		Encoder::exec("rm " + name);
	}

	std::string generateFolders(std::string userid, std::string videoid) {
		std::string path = "uploads/user_" + userid + "/video_" + videoid + "/";
		Encoder::exec("mkdir -p " + path);
		return path;
	}

	void like(std::string userid) {
		Cooper::ParameterBag data = Cooper::Http::get();

		if (userid.size() > 0 && data.exists("videoid")) {

			VideoRepository vr;
			vr.like(data.get("videoid"), userid);
			std::cout << "Content-type: text/html\r\n\r\n";

		} else {
			throw Cooper::Exceptions::FormException("Wrong request.");
		}
	}

	void view(std::string userid) {
		Cooper::ParameterBag data = Cooper::Http::get();

		VideoRepository vr;
		std::cout << "Content-type: text/html\r\n\r\n";
		vr.view(data.get("videoid"), userid);
	}

	std::vector<Video> getUserVideos(std::string userid) {
		VideoRepository vr;
		return vr.getUserVideos(userid);
	}

	std::vector<Video> getLikedVideos(std::string userid) {
		VideoRepository vr;
		return vr.getLikedVideos(userid);
	}

	std::vector<Video> getRecommendVideos(std::string userid) {
		VideoRepository vr;
		return vr.getNotViewedVideos(userid);
	}

	std::vector<Video> getAllVideos() {
		VideoRepository vr;
		return vr.getAllVideos();
	}

	std::string getViews(Video video) {
		VideoRepository vr;
		return vr.getViews(video.getId());
	}

	std::string getLikes(Video video) {
		VideoRepository vr;
		return vr.getLikes(video.getId());
	}
};