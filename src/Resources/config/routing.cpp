VC::Utils::_router loadRouting() {
	VC::Utils::_router router;

	router["main"] = new MainController();
	router["user"] = new UserController();

	return router;
}