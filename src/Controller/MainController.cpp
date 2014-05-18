using namespace Cooper;

// Main page rendering
class MainController : public Controller {
private:
	std::map <std::string, void(MainController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			(*this.*_methods[name])();
		} else {
			throw Exceptions::NotFoundException();
		}
	}

	MainController() {
		this->_methods["index"] = &MainController::indexAction;
	}

	void indexAction() {
		VideoService vs;

		VideoTemplate btpl("base");
		btpl.grid("content", vs.getAllVideos());
	
		std::cout << btpl.render();
	}	
};