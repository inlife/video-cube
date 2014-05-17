using namespace Cooper;

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
		std::map<std::string, std::string> data;
		// sample data
		data["id"] = "50";
		data["title"] = "Lorem ipsum";
		data["image"] = "img/temp/1.jpg";

		Template tpl("main/index");

		for(int i = 0; i < 3; i++) {
			Template line("main/_index-video-line");

			for(int i = 0; i < 3; i++) {
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