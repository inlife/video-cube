class MainController : public VC::Controller {
private:
	std::map <std::string, void(MainController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			this->sendOKHeaders();
			(*this.*_methods[name])();
		} else {
			throw VC::Exceptions::NotFoundException();
		}
	}

	MainController() {
		this->_methods["index"] = &MainController::indexAction;
	}

	void indexAction() {
		using namespace VC;

		std::map<std::string, std::string> data;
		// sample data
		data["id"] = "50";
		data["title"] = "Lorem ipsum";
		data["image"] = "img/temp/1.jpg";

		Template tpl = Template("base");

		for(int i = 0; i < 3; i++) {
			Template line = Template("_index-video-line");

			for(int i = 0; i < 3; i++) {
				Template box = Template("_index-video-box");

				box.set("id", data["id"]);
				box.set("title", data["title"]);
				box.set("image", data["image"]);

				line.add("videoline", box.render());
			}

			tpl.add("content", line.render());
		}

		std::cout << tpl.render();
	}	
};