class VideoService {
public:

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
			
			std::cout << "Content-type: text/html\r\n\r\n";
			std::cout << video.getId();

		} else {
			throw Cooper::Exceptions::FormException("Please, fill in all fields."); 
		}
	}

	std::string generateFolders(std::string userid, std::string videoid) {
		std::string path = "uploads/user/" + userid + "/video/" + videoid + "/";
		Encoder::exec("mkdir -p " + path);
		return path;
	}
};