using namespace Cooper;

// Video template grid
class VideoTemplate : public Template {
public:
	void grid(std::string name, std::vector<Video> videos) {
		this->set(name, "");

		double _l = videos.size() / 3.0;
		std::size_t length = std::ceil(_l);

		for(std::size_t i = 0; i < length; i++) {
			Template line("main/_index-video-line");

			for(std::size_t j = 0; j < 3; j++) {
				int id = ( i * 3 ) + j;
				if (id < videos.size()) {

					Template box("main/_index-video-box");

						box.set("id", videos[id].getId());
						box.set("title", videos[id].getTitle());
						box.set("preview", videos[id].getPreview());

					line.add("videoline", box.render(false));
				}
			}
			this->add(name, line.render(false));
		}
	}

	VideoTemplate(std::string name) : Template(name) {}
};