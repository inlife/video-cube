namespace Cooper {
	namespace Http {
		std::string getBaseUrl();
	}
	class Controller {
	public:
		virtual void _callAction(std::string name) {}

		void sendOKHeaders() {
			//std::cout << "Content-type: text/html\r\n\r\n";
		}

		void redirect(std::string name, std::string action) {

			std::string url = "Location: " + Http::getBaseUrl() + "?name=" + name + "&action=" + action + "\r\n";
			std::cout << url;
			std::cout << "Content-type: text/html\r\n\r\n";
		}
	};
}