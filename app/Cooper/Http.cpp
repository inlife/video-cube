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

		std::string urlEncode(const std::string &value) {
			using namespace std;

		    ostringstream escaped;
		    escaped.fill('0');
		    escaped << hex;

		    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		        string::value_type c = (*i);
		        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
		            escaped << c;
		        }
		        else if (c == ' ')  {
		            escaped << '+';
		        }
		        else {
		            escaped << '%' << setw(2) << ((int) c) << setw(0);
		        }
		    }

		    return escaped.str();
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

		std::string getBoundary() 
		{
			std::string line = std::getenv("CONTENT_TYPE");
			boost::algorithm::replace_all(line, "multipart/form-data; boundary=", "");
			return line;
		}
		
		ParameterBag cookies() {
			char const* tmp = getenv( "HTTP_COOKIE" );
			if ( tmp == NULL ) {
			    return ParameterBag();
			} else {
			    std::string line( tmp );
			    boost::algorithm::replace_all(line, "; ", "&");
				return parseParams(line);
			}
		}

		void setCookie(std::string name, std::string value) {
			std::cout << "Set-Cookie:" + name + "=" + urlEncode(value) + ";\r\n";
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
		/*
		ParameterBag file()
		{
			using namespace std;
			using namespace boost::algorithm;

			char* lpszContentLength = std::getenv("CONTENT_LENGTH");
			char* lpszBuffer;
			std::size_t nContentLength = std::atoi(lpszContentLength);
			
			lpszBuffer = (char*)std::malloc(nContentLength + 1); // allocate a buffer
			std::memset(lpszBuffer, 0, nContentLength + 1);  // zero it out

			std::fread(lpszBuffer, 1, nContentLength, stdin);  // get data

			string _data = string(lpszBuffer);
			string boundary = getBoundary();

			ParameterBag params;
		    std::vector <std::string> tokens;

		    iter_split(tokens, _data, first_finder("--" + boundary));

		    for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {

		    	if (it != tokens.begin() && it + 1 != tokens.end()) {
		    		string tmp = *it;
					replace_all(tmp, "Content-Disposition: form-data; name=\"", "");
					trim(tmp);
					if (tmp.find("filename") == std::string::npos) {
						replace_all(tmp, "\"\r\n\r\n", "-+@+-");

		    			std::vector <std::string> subtokens;
		    			iter_split(subtokens, tmp, first_finder("-+@+-"));

		    			params.add(subtokens[0], urlDecode(subtokens[1]));
					} else {
						replace_all(tmp, "\"; filename=\"", "-+@+-");
						replace_all(tmp, "\r\n\r\n", "-+T+-");
		    			std::vector <std::string> subtokens1, subtokens2;

		    			iter_split(subtokens1, tmp, first_finder("-+@+-"));
		    			iter_split(subtokens2, tmp, first_finder("-+T+-"));
						
		    			params.add(subtokens1[0], subtokens2[1]);
					}
		    	}
		    }
			
			return params;
		}
		*/
	}
}