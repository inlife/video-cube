namespace VC {

	namespace Exceptions {

		class NotFoundException : public std::exception {
		public:
			virtual const char* getMessage() const throw() {
				return "404 - Page not found.";
			}
		};
	}
}