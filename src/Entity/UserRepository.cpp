class UserRepository : public Cooper::EntityRepository {
public:
	User load(Cooper::Http::ParameterBag data) {
		// sample
		return User(data["login"], data["password"]);
	}

	User create(Cooper::Http::ParameterBag data) {
		User user = User();

		//if (data.find("login")) {
		//	std::cout << "true!";
		//}
		return user;
	}
};