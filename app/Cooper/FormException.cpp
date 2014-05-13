namespace Cooper {

	namespace Exceptions {

		class FormException {
			std::string message;
		public:
			std::string getMessage() {
				return this->message.c_str();
			}

			FormException(std::string message) {
				this->message = message;
			}
		};
	}
}