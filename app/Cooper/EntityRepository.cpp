namespace Cooper {
	
	class EntityRepository {
	protected:

		std::vector< std::map<std::string, std::string> > query(int type, std::string sql) {
			std::vector< std::map<std::string, std::string> > result;

			pqxx::connection C(
				" dbname="	 + Cooper::config["dbname"] +
				" user="  	 + Cooper::config["user"] +
				" password=" + Cooper::config["password"]  +
      			" hostaddr=" + Cooper::config["hostaddr"] +
      			" port=" 	 + Cooper::config["port"] 
      		);

			if (C.is_open()) {
				if (type == 1) {
					
					//transactional
					pqxx::work W(C);
		      
					W.exec( sql );
					W.commit();

				} else {
					// non-transactional
					pqxx::nontransaction N(C);
	      
					/* Execute SQL query */
					pqxx::result R( N.exec( sql ));

					for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
						std::map<std::string, std::string> row;

						for (pqxx::const_tuple_iterator i = c.begin(); i != c.end(); ++i) {
							row[i.name()] = i.as<std::string>();
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