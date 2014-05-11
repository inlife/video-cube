class UserRepository : public VC::EntityRepository {
public:
	User *load(VC::Utils::_params data) {
		// sample
		return new User(data["login"], data["password"]);
	}

	User *create(VC::Utils::_params data) {
		return new User(data["login"], data["password"]);
	}
};