using namespace Cooper;

class UserController : public Controller {
private:
	std::map <std::string, void(UserController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			this->sendOKHeaders();
			(*this.*_methods[name])();
		} else {
			throw Cooper::Exceptions::NotFoundException();
		}
	}

	UserController() {
		this->_methods["index"] = &UserController::indexAction;
		this->_methods["login"] = &UserController::loginAction;
		this->_methods["register"] = &UserController::registerAction;
	}

	void indexAction() {

		Template tpl = Template("login");

		//tpl.set("content", "");
	
		std::cout << tpl.render();
	}

	void loginAction() {

		UserRepository repo = UserRepository();

		User user = repo.load(Http::post());

		std::cout << "Your login: " << user.getName() << "<br>";
		std::cout << "Your password: " << user.getPassword() << "<br>";
	}

	void registerAction() {
		UserRepository repo = UserRepository();

		repo.create(Http::post());
		//User *user = repo.create();

	}
};