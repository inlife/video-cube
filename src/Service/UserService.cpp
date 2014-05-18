// Implementation of user Services
class UserService {
public:

	// Chek if logged in
	bool isLogined() {
		Cooper::ParameterBag data = Cooper::Http::cookies();
		UserRepository repository = UserRepository();

		if (data.exists("login") && data.exists("password")) {
			return repository.exists(data.get("login"), data.get("password"));
		}
		
		return false;
	}

	// Load, using ParametrBag data
	User load() {
		Cooper::ParameterBag data = Cooper::Http::cookies();
		UserRepository repository = UserRepository();

		User user = repository.load(
			data.get("login"), 
			data.get("password")
		);

		return user;
	}

	// Save some cookies 
	void logout() {
		Cooper::Http::setCookie("login", "");
		Cooper::Http::setCookie("password", "");
	}

	User getUser() {
		return this->load();
	}

	// User creation Service
	User create(Cooper::ParameterBag data) {

		if (this->isLogined()) throw Cooper::Exceptions::FormException("Already logined in.");

		if (data.exists("login") && data.exists("password") && data.exists("repassword")) {
			
			if (data.get("password") != data.get("repassword")) {
				throw Cooper::Exceptions::FormException("Passwords are not equal.");
			}
			
			UserRepository repository = UserRepository();

			if (!repository.exists(data.get("login"))) {

				User user = repository.create(
					data.get("login"), 
					data.get("password")
				);

				return user;
			} else {
				throw Cooper::Exceptions::FormException("Username is already taken");
			}

		} else {
			throw Cooper::Exceptions::FormException("Please, fill in all fields.");
		}
	}

	// User login Service
	User login(Cooper::ParameterBag data) {

		if (this->isLogined()) throw Cooper::Exceptions::FormException("Already logined in.");
		
		if (data.exists("login") && data.exists("password")) {

			UserRepository repository = UserRepository();

			if (repository.exists(data.get("login"), data.get("password"))) {

				User user = repository.load(
					data.get("login"), 
					data.get("password")
				);

				Cooper::Http::setCookie("login", 	data.get("login"));
				Cooper::Http::setCookie("password", data.get("password"));

				return user;
			} else {
				throw Cooper::Exceptions::FormException("User doesn't exists");
			}

		} else {
			throw Cooper::Exceptions::FormException("Please, fill in all fields.");
		}
	}
};