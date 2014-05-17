Cooper::Http::_router loadRouting() {
	Cooper::Http::_router router;

	router["main"] = new MainController();
	router["user"] = new UserController();
	router["video"] = new VideoController();

	return router;
}

/*using namespace Cooper;
void loadParams() {
	config["dbname"] = "videocube";
	config["user"] = "postgres";
	config["password"] = "1we2q3";
	config["hostaddr"] = "93.73.16.132";
	config["port"] = "5432";
}*/