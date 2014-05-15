class UserRepository : public Cooper::EntityRepository {
public:

	bool exists(std::string login, std::string password) {
		std::string sql = "SELECT COUNT(*) FROM \"user\" WHERE login='";
			sql.append( login );

			if (password.size() > 0) {
				sql.append( "' AND password='" );
				sql.append( password );
				sql.append( "'" );
			} else {
				sql.append( "'" );
			}

		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		int usrcnt = std::atoi(result[0].get("count").c_str());
		return (usrcnt > 0);
	}

	bool exists(std::string login) {
		return this->exists(login, std::string(""));
	}

	User load(std::string login, std::string password) {

		std::string sql = "SELECT * FROM \"user\" WHERE login='";
			sql.append( login );
			sql.append( "' AND password='" );
			sql.append( password );
			sql.append( "'" );
		
		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		
		User user = User();

		user.setId(result[0]["id"]);
		user.setLogin(result[0]["login"]);
		user.setPassword(result[0]["password"]);

		return user;
	}

	User create(std::string login, std::string password) {
		
		std::string sql = "INSERT INTO \"user\" (login, password) VALUES ('";
			sql.append( login );
			sql.append( "', '" );
			sql.append( password );
			sql.append( "')" );

			this->query(1, sql);

		return this->load(login, password);
	}
};