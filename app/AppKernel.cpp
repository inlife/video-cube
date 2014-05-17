#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <map>      
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>


#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/filesystem.hpp>

#include <pqxx/pqxx> 

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>

#include "../src/Encoder.h"

#include "Cooper/NotFoundException.cpp"
#include "Cooper/InternalErrorException.cpp"
#include "Cooper/FormException.cpp"
#include "Cooper/ParameterBag.cpp"
#include "Cooper/Controller.cpp"
#include "Cooper/Http.cpp"
#include "Cooper/Template.cpp"
#include "Cooper/EntityRepository.cpp"


#include "../src/Entity/Video.cpp"
#include "../src/Entity/User.cpp"

#include "../src/Entity/VideoRepository.cpp"
#include "../src/Service/VideoService.cpp"

#include "../src/Entity/UserRepository.cpp"
#include "../src/Service/UserService.cpp"

#include "../src/Controller/MainController.cpp"
#include "../src/Controller/UserController.cpp"
#include "../src/Controller/VideoController.cpp"

#include "../src/Resources/config/routing.cpp"
#include "../src/Resources/config/parameters.cpp"


//char *value = std::getenv( ENV[ i ].c_str() );  
const std::string ENV[ 24 ] = {                 
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_IN	TERFACE",   
    "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
    "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
    "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
    "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
    "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
    "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
    "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
    "SERVER_SIGNATURE","SERVER_SOFTWARE" };

int main() {

    loadParams();
    
    Cooper::Http::_router router = loadRouting();
	Cooper::ParameterBag params = Cooper::Http::get();

	try {
		if (router.find(params["name"]) != router.end()) {
			router[params["name"]]->_callAction(params["action"]);
		} else {
			throw Cooper::Exceptions::NotFoundException();
		}
	} catch (Cooper::Exceptions::FormException &e) {

        if (params.get("type") == "ajax") {

            std::cout << "Status: 500 Internal Server Error\r\n\n";
            std::cout << e.getMessage();

        } else {

            Template tpl = Template("error/index");

            tpl.set("message", e.getMessage());
            std::cout << tpl.render();
        }

    } catch (Cooper::Exceptions::NotFoundException &e) {

		std::cout << "Status: 404 Not Found\r\n\n";
		std::cout << e.getMessage() << std::endl;

	} catch (Cooper::Exceptions::InternalErrorException &e) {

        std::cout << "Status: 500 Internal Server Error\r\n\n";
        std::cout << e.getMessage() << std::endl;

    } catch (std::exception &e) {
        std::cout << "Content-type: text/html\r\n\r\n";
        std::cout << e.what();
    }
	return 0;
};
