namespace Cooper {

	namespace Exceptions {

		class InternalErrorException : public std::exception {
		public:
			virtual const char* getMessage() const throw() {
				return "500 - Internal Server Error.";
			}
		};
	}
}