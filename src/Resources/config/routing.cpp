// Basic conroller routing
Cooper::Http::_router loadRouting() {
	Cooper::Http::_router router;

	router["main"]  = new MainController();
	router["user"]  = new UserController();
	router["video"] = new VideoController();

	return router;
}