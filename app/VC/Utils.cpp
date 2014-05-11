namespace VC {

	namespace Utils {

		typedef std::map <std::string, Controller*> _router;
		typedef std::map <std::string, std::string> _params;

		std::string getBaseUrl() {
			std::string host = std::getenv("HTTP_HOST");
			std::string path = std::getenv("SCRIPT_NAME");

			boost::algorithm::replace_all(path, "app.cgi", "");

			return "http://" + host + path;
		}


		_params parseParams(std::string query) {

			using namespace boost::algorithm;

			_params params;
		    std::vector <std::string> tokens;

		    split(tokens, query, is_any_of("&")); 

		    for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {

		    	std::vector <std::string> subtokens;
		    	split(subtokens, *it, is_any_of("="));
		    	
		    	params[subtokens[0]] = subtokens[1];
		    }

		    if (params.find("name") == params.end()) {
		    	params["name"] = "main";
		    }
		    if (params.find("action") == params.end()) {
		    	params["action"] = "index";
		    }

		    return params;
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

		std::string getPost()
		{
			using namespace std;

			char* lpszContentLength = getenv("CONTENT_LENGTH");
			char* lpszBuffer;
			size_t nContentLength = atoi(lpszContentLength);
			
			lpszBuffer = (char*)malloc(nContentLength + 1); // allocate a buffer
			memset(lpszBuffer, 0, nContentLength + 1);  // zero it out

			fread(lpszBuffer, 1, nContentLength, stdin);  // get data
			
			return urlDecode(string(lpszBuffer));
		}
	}
}