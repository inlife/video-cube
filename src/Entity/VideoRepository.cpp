class VideoRepository : public Cooper::EntityRepository {
public: 

	bool exists(std::string id) {
		std::string sql = "SELECT COUNT(*) FROM \"video\" WHERE id=";
			sql.append( id );

		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		int usrcnt = std::atoi(result[0].get("count").c_str());
		return (usrcnt > 0);
	}
	
	Video create(std::string userid, std::string title) {

		std::string sql = "INSERT INTO \"video\" (userid, title, chunks) VALUES ('";
			sql.append( userid );
			sql.append( "', '" );
			sql.append( title );
			sql.append( "', '0')" );

			this->query(1, sql);

		return this->load(userid, title);
	}

	Video load(std::string id) {

		std::string sql = "SELECT * FROM \"video\" WHERE id=";
			sql.append( id );
		
		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		
		Video video = Video();

		video.setId(result[0]["id"]);
		video.setTitle(result[0]["title"]);
		video.setUserId(result[0]["userid"]);
		video.setChunks(result[0]["chunks"]);

		return video;
	}

	Video load(std::string userid, std::string title) {

		std::string sql = "SELECT * FROM \"video\" WHERE userid='";
			sql.append( userid );
			sql.append( "' AND title='" );
			sql.append( title );
			sql.append( "' ORDER BY id DESC LIMIT 1" );
		
		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		
		Video video = Video();

		video.setId(result[0]["id"]);
		video.setTitle(result[0]["title"]);
		video.setUserId(result[0]["userid"]);
		video.setChunks(result[0]["chunks"]);

		return video;
	}

	void updateChunks(Video video) {
		std::string sql = "UPDATE \"video\" SET chunks='";
			sql.append( video.getChunks() );
			sql.append( "' WHERE id=" + video.getId() );

			this->query(1, sql);
	}

	void like(std::string videoid, std::string userid) {
		std::string sql = "INSERT INTO \"like\" (userid, videoid) SELECT '";
			sql.append( userid );
			sql.append( "', '" );
			sql.append( videoid );
			sql.append( "' WHERE NOT EXISTS ( SELECT id FROM \"like\" WHERE userid = '" );
			sql.append( userid );
			sql.append( "' AND videoid = '" );
			sql.append( videoid );
			sql.append( "')" );

		this->query(1, sql);
	}

	void view(std::string videoid, std::string userid) {
		std::string sql = "INSERT INTO \"view\" (userid, videoid) VALUES ('";
			sql.append( userid );
			sql.append( "', '" );
			sql.append( videoid );
			sql.append( "')" );

		this->query(1, sql);
	}

	std::vector<Video> toObjects(std::vector<Cooper::ParameterBag> videos) {
		std::vector<Video> result;

		for(std::size_t i = 0; i < videos.size(); i++) {
			Video video;
				video.setId(videos[i].get("id"));
				video.setTitle(videos[i].get("title"));
				video.setUserId(videos[i].get("userid"));
				video.setChunks(videos[i].get("chunks"));
			result.push_back(video);
		}
		return result;
	}

	std::vector<Video> getUserVideos(std::string userid) {
		std::string sql = "SELECT * FROM \"video\" WHERE userid='";
			sql.append( userid );
			sql.append( "'" );
		
		return this->toObjects(
			this->query(2, sql)
		);
	}

	std::vector<Video> getLikedVideos(std::string userid) {
		std::string sql = "SELECT * FROM \"video\" WHERE id IN ( SELECT CAST(videoid AS integer) FROM \"like\" WHERE userid='";
			sql.append( userid );
			sql.append( "')" );
		
		return this->toObjects(
			this->query(2, sql)
		);
	}

	std::vector<Video> getNotViewedVideos(std::string userid) {
		std::string sql = "SELECT * FROM \"video\" WHERE id NOT IN ( SELECT CAST(videoid AS integer) FROM \"view\" WHERE userid='";
			sql.append( userid );
			sql.append( "') AND id NOT IN ( SELECT CAST(videoid AS integer) FROM \"like\" WHERE userid='");
			sql.append( userid );
			sql.append( "')" );
		
		return this->toObjects(
			this->query(2, sql)
		);
	}

	std::vector<Video> getAllVideos() {
		std::string sql = "SELECT * FROM \"video\"";
		
		return this->toObjects(
			this->query(2, sql)
		);
	}
	
	std::string getViews(std::string videoid) {
		std::string sql = "SELECT COUNT(*) FROM \"view\" WHERE videoid = '";
			sql.append( videoid );
			sql.append( "'" );

		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		return result[0].get("count");
	}
	
	std::string getLikes(std::string videoid) {
		std::string sql = "SELECT COUNT(*) FROM \"like\" WHERE videoid = '";
			sql.append( videoid );
			sql.append( "'" );

		std::vector<Cooper::ParameterBag> result = this->query(2, sql);
		return result[0].get("count");
	}
};