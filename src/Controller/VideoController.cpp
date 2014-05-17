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
		this->_methods["upload"] = &VideoController::ajaxUplaodAction;
		this->_methods["add"] = &VideoController::addAction;
	}

	void ajaxUplaodAction() {
		UserService us = UserService();
		if (!us.isLogined()) this->redirect("user", "login");
		
		VideoService vs = VideoService();
		vs.upload(us.getUser());
	}

	void addAction() {
		Template tpl("video/add");
		std::cout << tpl.render();
	}
};