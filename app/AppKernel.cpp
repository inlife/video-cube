// Basic includes
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
#include <math.h> 

// Include boost library for some simplification
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/filesystem.hpp>

// Library to work with Posgress SQL
#include <pqxx/pqxx> 

// Library to wotk with cgi
#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>

// Our video converter and cutter
#include "../src/Encoder.h"

// Self mini-framework for some simpification
#include "Cooper/NotFoundException.cpp"
#include "Cooper/InternalErrorException.cpp"
#include "Cooper/FormException.cpp"
#include "Cooper/ParameterBag.cpp"
#include "Cooper/Controller.cpp"
#include "Cooper/Http.cpp"
#include "Cooper/Template.cpp"
#include "Cooper/EntityRepository.cpp"

// Classes that represents entities in Database
#include "../src/Entity/Video.cpp"
#include "../src/Entity/User.cpp"

// Classes to communicate with Database
#include "../src/Entity/VideoRepository.cpp"
#include "../src/Entity/UserRepository.cpp"

// Classes to implement business logic
#include "../src/Service/VideoService.cpp"
#include "../src/Service/UserService.cpp"

// Extended templete for video data
#include "../src/Template/VideoTemplate.cpp"

// Classes that control extended routing
#include "../src/Controller/MainController.cpp"
#include "../src/Controller/UserController.cpp"
#include "../src/Controller/VideoController.cpp"

// Classes that control routing
#include "../src/Resources/config/routing.cpp"
#include "../src/Resources/config/parameters.cpp"

int main() {

    // Load parameters to work with DB
    loadParams();
    
    // Get data from brouser
    Cooper::Http::_router router = loadRouting();
	Cooper::ParameterBag params = Cooper::Http::get();

    // Main application code
	try {
		if (router.find(params["name"]) != router.end()) {
			router[params["name"]]->_callAction(params["action"]);
		} else {
			throw Cooper::Exceptions::NotFoundException();
		}
	} catch (Cooper::Exceptions::FormException &e) {
        
        // Plain text error message
        if (params.get("type") == "ajax") {

            std::cout << "Status: 500 Internal Server Error\r\n\n";
            std::cout << e.getMessage();

        } else {
        // Template error message
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
        std::cout << "Status: 500 Internal Server Error\r\n\n";
        std::cout << e.what();
    }
	return 0;
};
