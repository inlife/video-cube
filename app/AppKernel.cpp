#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "VC/Controller.cpp"
#include "VC/Utils.cpp"
#include "VC/Template.cpp"
#include "VC/EntityRepository.cpp"
#include "VC/NotFoundException.cpp"

#include "../src/Entity/User.cpp"
#include "../src/Entity/UserRepository.cpp"
#include "../src/Controller/MainController.cpp"
#include "../src/Controller/UserController.cpp"
#include "../src/Resources/config/routing.cpp"

//char *value = std::getenv( ENV[ i ].c_str() );  
const std::string ENV[ 24 ] = {                 
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
    "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
    "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
    "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
    "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
    "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
    "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
    "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
    "SERVER_SIGNATURE","SERVER_SOFTWARE" };   


int main() {

    VC::Utils::_router router = loadRouting();
	VC::Utils::_params params = VC::Utils::parseParams(
        std::getenv("QUERY_STRING")
    );

	try {
		if (router.find(params["name"]) != router.end()) {
			router[params["name"]]->_callAction(params["action"]);
		} else {
			throw VC::Exceptions::NotFoundException();
		}
	} catch (VC::Exceptions::NotFoundException &e) {
		std::cout << "Status: 404 Not Found\r\n\n";
		std::cout << e.getMessage() << std::endl;
	}

	return 0;
};
