namespace Cooper {

	// Defining of undefined functions
	namespace Http {
		std::string getBaseUrl();
	}
	
	// Base class to handle user actions 
	class Controller {
	public:

		virtual void _callAction(std::string name) {}

		void redirect(std::string name, std::string action) {

			std::string url = "Location: " + Http::getBaseUrl() + "?name=" + name + "&action=" + action + "\r\n";
			std::cout << url;
			std::cout << "Content-type: text/html\r\n\r\n";
		}
	};
}