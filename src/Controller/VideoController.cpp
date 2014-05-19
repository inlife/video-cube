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
		this->_methods["like"] = &VideoController::ajaxLikeAction;
		this->_methods["view"] = &VideoController::ajaxViewAction;
	}

	void indexAction() {
		Template btpl("base");
		VideoTemplate tpl("video/player");

		VideoService vs;
		Video video = vs.getPlayerVideo();

		tpl.set("title", video.getTitle());
		tpl.list("videos", vs.getOtherVideos(video));

		btpl.set("content", tpl.render(false));

		btpl.set("videoid", video.getId());
		btpl.set("videourl", video.getUrl());
		btpl.set("chunks", video.getChunks());
		btpl.set("views", vs.getViews(video));
		btpl.set("likes", vs.getLikes(video));
		

		std::cout << btpl.render();
	}

	void ajaxUplaodAction() {
		UserService us;
		if (!us.isLogined()) this->redirect("user", "login");
		
		VideoService vs = VideoService();
		vs.upload(us.getUser());
	}

	void ajaxLikeAction() {
		UserService us;
		if (!us.isLogined()) return throw Exceptions::FormException("User not logined");

		VideoService vs;
		vs.like(us.getUser().getId());
	}

	void ajaxViewAction() {
		UserService us;
		VideoService vs;

		if (us.isLogined()) {
			vs.view(us.getUser().getId());
		} else {
			vs.view("");
		}
	}

	void addAction() {
		Template btpl("base");
		Template tpl("video/add");

		btpl.set("content", tpl.render(false));

		std::cout << btpl.render();
	}

	void likesAction() {
		UserService  us;
		VideoService vs;

		if (!us.isLogined()) return this->redirect("user", "index");

		User user = us.getUser();

		VideoTemplate btpl("base");
		btpl.grid("content", vs.getLikedVideos(
			user.getId()
		));
	
		std::cout << btpl.render();
	}

	void recommendAction() {
		UserService  us;
		VideoService vs;

		if (!us.isLogined()) return this->redirect("user", "index");

		User user = us.getUser();

		VideoTemplate btpl("base");
		btpl.grid("content", vs.getRecommendVideos(
			user.getId()
		));
	
		std::cout << btpl.render();
	}
};