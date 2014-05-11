namespace VC {
	
	class Controller {
	public:
		virtual void _callAction(std::string name) {}

		void sendOKHeaders() {
			std::cout << "Content-type: text/html\r\n\r\n";
		}
	};
}