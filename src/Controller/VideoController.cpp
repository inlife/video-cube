using namespace Cooper;

class VideoController : public Controller {
private:
	std::map <std::string, void(VideoController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			(*this.*_methods[name])();
		} else {
			throw Cooper::Exceptions::NotFoundException();
		}
	}

	VideoController() {
		this->_methods["index"] = &VideoController::indexAction;
		this->_methods["upload"] = &VideoController::ajaxUplaodAction;
		this->_methods["add"] = &VideoController::addAction;
		this->_methods["likes"] = &VideoController::likesAction;
		this->_methods["recommend"] = &VideoController::recommendAction;
	}

	void indexAction() {
		Template btpl("base");
		Template tpl("video/player");

		VideoService vs;
		Video video = vs.getPlayerVideo();

		tpl.set("title", video.getTitle());

		btpl.set("content", tpl.render(false));

		btpl.set("videourl", video.getUrl());
		btpl.set("chunks", video.getChunks());

		std::cout << btpl.render();
	}

	void ajaxUplaodAction() {
		UserService us;
		if (!us.isLogined()) this->redirect("user", "login");
		
		VideoService vs = VideoService();
		vs.upload(us.getUser());
	}

	void addAction() {
		Template btpl("base");
		Template tpl("video/add");

		btpl.set("content", tpl.render(false));

		std::cout << btpl.render();
	}

	void likesAction() {
		std::map<std::string, std::string> data;
		// sample data
		data["id"] = "50";
		data["title"] = "Lorem ipsum";
		data["image"] = "img/temp/1.jpg";

		Template tpl("base");

		for (int i = 0; i < 3; i++) {
			Template line("main/_index-video-line");

			for (int i = 0; i < 3; i++) {
				Template box("main/_index-video-box");

				box.set("id", data["id"]);
				box.set("title", data["title"]);
				box.set("image", data["image"]);

				line.add("videoline", box.render(false));
			}

			tpl.add("content", line.render(false));
		}

		std::cout << tpl.render();
	}

	void likeAction() {

	}

	void recommendAction() {
		std::map<std::string, std::string> data;
		// sample data
		data["id"] = "50";
		data["title"] = "Lorem ipsum";
		data["image"] = "img/temp/1.jpg";

		Template tpl("base");

		for (int i = 0; i < 3; i++) {
			Template line("main/_index-video-line");

			for (int i = 0; i < 3; i++) {
				Template box("main/_index-video-box");

				box.set("id", data["id"]);
				box.set("title", data["title"]);
				box.set("image", data["image"]);

				line.add("videoline", box.render(false));
			}

			tpl.add("content", line.render(false));
		}

		std::cout << tpl.render();
	}
};