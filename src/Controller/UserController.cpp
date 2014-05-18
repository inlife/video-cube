using namespace Cooper;

// Handle response to work with user actions
class UserController : public Controller {
private:
	std::map <std::string, void(UserController::*)()> _methods;

public: 

	void _callAction(std::string name) {
		if (this->_methods.find(name) != this->_methods.end()) {
			(*this.*_methods[name])();
		} else {
			throw Exceptions::NotFoundException();
		}
	}

	UserController() {
		this->_methods["index"] = &UserController::indexAction;
		this->_methods["cabinet"] = &UserController::cabinetAction;
		this->_methods["login"] = &UserController::loginAction;
		this->_methods["logout"] = &UserController::logoutAction;
		this->_methods["register"] = &UserController::registerAction;
	}

	// Handle if you logined in
	void indexAction() {
		UserService us = UserService();
		if (us.isLogined()) return this->redirect("user", "cabinet");

		Template tpl("user/login-register-form");
		tpl.set("message", "Hello guest, please log in or register!");
	
		std::cout << tpl.render();
	}

	// Render cabinet
	void cabinetAction() {
		UserService  us;
		VideoService vs;

		if (!us.isLogined()) return this->redirect("user", "index");

		User user = us.getUser();

		Template btpl("base");
		VideoTemplate tpl("user/cabinet");

		tpl.set("userlogin", user.getLogin());
		tpl.grid("videos", vs.getUserVideos(
			user.getId()
		));

		btpl.set("content", tpl.render(false));
	
		std::cout << btpl.render();
	}

	void loginAction() {
		UserService us;
		User user = us.login(Http::post());

		return this->redirect("user", "cabinet");
	}

	void logoutAction() {
		UserService us;

		us.logout();
		return this->redirect("main", "index");
	}

	void registerAction() {
		UserService us;
		User user = us.create(Http::post());

		Template tpl("user/login-register-form");
		tpl.set("message", "Thank you, " + user.getLogin() + ". Now you can log in.");

		std::cout << tpl.render();
	}
};