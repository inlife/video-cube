namespace Cooper {

	std::map<std::string, std::string> config;

	namespace Http {

		typedef std::map <std::string, Controller*> _router;

		std::string getBaseUrl() {
			std::string host = std::getenv("HTTP_HOST");
			std::string path = std::getenv("SCRIPT_NAME");

			boost::algorithm::replace_all(path, "app.cgi", "");

			return "http://" + host + path;
		}

		std::string urlDecode(std::string SRC) {
		    std::string ret;
		    char ch;
		    int i, ii;
		    for (i=0; i<SRC.length(); i++) {
		        if (int(SRC[i])==37) {
		            std::sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
		            ch=static_cast<char>(ii);
		            ret+=ch;
		            i=i+2;
		        } else {
		            ret+=SRC[i];
		        }
		    }
		    return (ret);
		}

		ParameterBag parseParams(std::string query) {

			using namespace boost::algorithm;

			ParameterBag params;
		    std::vector <std::string> tokens;

		    split(tokens, query, is_any_of("&")); 

		    for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {

		    	std::vector <std::string> subtokens;
		    	split(subtokens, *it, is_any_of("="));
		    	
		    	params.add(subtokens[0], urlDecode(subtokens[1]));
		    }

		    return params;
		}

		ParameterBag cookies() {
			std::string line = std::getenv("HTTP_COOKIE");
			if (line.size() > 0) {
				boost::algorithm::replace_all(line, "; ", "&");
				return parseParams(line);
			} else {
				return ParameterBag();
			}
		}

		ParameterBag get() {
			ParameterBag params = parseParams(std::getenv("QUERY_STRING"));

		    if (!params.exists("name")) {
		    	params.set("name", "main");
		    }
		    if (!params.exists("action")) {
		    	params.set("action", "index");
		    }
		    return params;
		}

		ParameterBag post()
		{
			using namespace std;

			char* lpszContentLength = std::getenv("CONTENT_LENGTH");
			char* lpszBuffer;
			std::size_t nContentLength = std::atoi(lpszContentLength);
			
			lpszBuffer = (char*)std::malloc(nContentLength + 1); // allocate a buffer
			std::memset(lpszBuffer, 0, nContentLength + 1);  // zero it out

			std::fread(lpszBuffer, 1, nContentLength, stdin);  // get data

			return parseParams(std::string(lpszBuffer));
		}
	}
}