namespace Cooper {
	
	class EntityRepository {
		pqxx::connection *connection;

	protected:
		void connect() {
			this->connection = NULL;
			try{
				pqxx::connection C(
					" dbname="	 + Cooper::config["dbname"] +
					" user="  	 + Cooper::config["user"] +
					" password=" + Cooper::config["password"]  +
	      			" hostaddr=" + Cooper::config["hostaddr"] +
	      			" port=" 	 + Cooper::config["port"] 
	      		);

				if (C.is_open()) {
	      			this->connection = &C;
      			} else {
      				throw Exceptions::InternalErrorException();
      			}
	      	} catch (std::exception e) {
	      		throw Exceptions::InternalErrorException();
	      	}
		}

		void disconnect() {
			if (this->connection != NULL) {
				this->connection->disconnect();
			}
		}

		std::vector< std::map<std::string, std::string> > query(int type, std::string sql) {
			std::vector< std::map<std::string, std::string> > result;

			if (type == 1) {
				//transactional
				pqxx::work W(*this->connection);
	      
				W.exec( sql );
				W.commit();

			} else {
				// non-transactional
				pqxx::nontransaction N(*this->connection);
      
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
			return result;
		}

	public:
		EntityRepository() {
			this->connect();
		}

		~EntityRepository() {
			this->disconnect();
		}
	};
	
};