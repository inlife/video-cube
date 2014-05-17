class VideoRepository : public Cooper::EntityRepository {
public: 
	
	Video create(std::string userid, std::string title) {

		std::string sql = "INSERT INTO \"video\" (userid, title, chunks) VALUES ('";
			sql.append( userid );
			sql.append( "', '" );
			sql.append( title );
			sql.append( "', '0')" );

			this->query(1, sql);

		return this->load(userid, title);
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

		return video;
	}

	void updateChunks(Video video) {
		std::string sql = "UPDATE \"video\" SET chunks='";
			sql.append( video.getChunks() );
			sql.append( "' WHERE id=" + video.getId() );

			this->query(1, sql);
	}
};