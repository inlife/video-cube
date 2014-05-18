namespace Cooper {
	
	// Base class for other repositories
	class EntityRepository {
	protected:

		// Establishing connection with DB
		std::vector<ParameterBag> query(int type, std::string sql) {
			std::vector<ParameterBag> result;

			pqxx::connection C(
				" dbname="	 + Cooper::config["dbname"] +
				" user="  	 + Cooper::config["user"] +
				" password=" + Cooper::config["password"]  +
      			" hostaddr=" + Cooper::config["hostaddr"] +
      			" port=" 	 + Cooper::config["port"] 
      		);

			if (C.is_open()) {
				if (type == 1) {
					
					// Transactional
					pqxx::work W(C);
		      
					W.exec( sql );
					W.commit();

				} else {
					// Non-transactional
					pqxx::nontransaction N(C);
	      
					// Execute SQL query
					pqxx::result R( N.exec( sql ));

					// Formating query results
					for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
						ParameterBag row;

						for (pqxx::const_tuple_iterator i = c.begin(); i != c.end(); ++i) {
							row.add(i.name(),  i.as<std::string>());
						}

						result.push_back(row);
					}
				}

				C.disconnect();
			}
			return result;
		}

	public:
		EntityRepository() {}
	};
	
};