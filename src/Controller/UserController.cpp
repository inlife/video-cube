class UserController : public VC::Controller {
private:
	std::map <std::string, void(UserController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			this->sendOKHeaders();
			(*this.*_methods[name])();
		} else {
			throw VC::Exceptions::NotFoundException();
		}
	}

	UserController() {
		this->_methods["index"] = &UserController::indexAction;
		this->_methods["login"] = &UserController::loginAction;
		this->_methods["register"] = &UserController::registerAction;
	}

	void indexAction() {
		using namespace VC;

		Template tpl = Template("login");

		//tpl.set("content", "");
	
		std::cout << tpl.render();
	}

	void loginAction() {
		using namespace VC;

		Utils::_params params = Utils::parseParams(
			Utils::getPost()
		);

		UserRepository repo = UserRepository();

		User *user = repo.load(params);

		std::cout << "Your login: " << user->getName() << "<br>";
		std::cout << "Your password: " << user->getPassword() << "<br>";
	}

	void registerAction() {
		using namespace VC;

		Utils::_params params = Utils::parseParams(
			Utils::getPost()
		);

		UserRepository repo = UserRepository();

		User *user = repo.create(params);

		std::cout << "Your login: " << user->getName() << "<br>";
		std::cout << "Your password: " << user->getPassword() << "<br>";
	}
};