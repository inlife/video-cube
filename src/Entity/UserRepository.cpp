class UserRepository : public Cooper::EntityRepository {
public:
	User load(Cooper::Http::ParameterBag data) {
		// sample
		return User(data["login"], data["password"]);
	}

	User create(Cooper::Http::ParameterBag data) {
		User user = User();

		if (data.exists("login") && data.exists("password") && data.exists("repassword")) {
			
			if (data.get("password") != data.get("repassword")) {
				throw Cooper::Exceptions::FormException("Passwords are not equal.");
			}
			
			// no hashing
			std::string sql1 = "INSERT INTO \"user\" (id, login, password) VALUES (2, '";
				sql1.append( data.get("login") );
				sql1.append( "', '" );
				sql1.append( data.get("password") );
				sql1.append( "')" );

				std::cout <<sql1;

			this->query(1, sql1);

			//std::string sql2 = "select * from users where (login)"

			return user;

		} else {
			throw Cooper::Exceptions::FormException("Please, fill in all fields.");
		}
	}
};