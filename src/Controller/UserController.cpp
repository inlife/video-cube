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
		this->_methods["cabinet"] = &UserController::cabinetAction;
		this->_methods["login"] = &UserController::loginAction;
		this->_methods["register"] = &UserController::registerAction;
	}

	void indexAction() {
		UserService us = UserService();
		if (us.isLogined()) this->redirect("user", "cabinet");
		

		Template tpl = Template("user/index");
		tpl.set("message", "Hello guest, please log in or register!");
	
		std::cout << tpl.render();
	}

	void cabinetAction() {
		UserService us = UserService();
		if (!us.isLogined()) this->redirect("user", "index");
		

		Template tpl = Template("user/cabinet");
		tpl.set("message", "Hello guest, please log in or register!");
		tpl.set("userlogin", us.load().getLogin());
	
		std::cout << tpl.render();
	}

	void loginAction() {
		UserService us = UserService();
		User user = us.login(Http::post());

		this->redirect("user", "cabinet");
	}

	void registerAction() {
		UserService us = UserService();
		User user = us.create(Http::post());

		Template tpl = Template("user/index");
		tpl.set("message", "Thank you, " + user.getLogin() + ". Now you can log in.");

		std::cout << tpl.render();
	}
};