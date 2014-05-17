namespace Encoder {

	using namespace std;

	string exec(string cmd) {
	    FILE* pipe = popen(cmd.c_str(), "r");
	    if (!pipe) return "ERROR";
	    char buffer[128];
	    string result = "";
	    while(!feof(pipe)) {
	    	if(fgets(buffer, 128, pipe) != NULL)
	    		result += buffer;
	    }
	    pclose(pipe);
	    return result;
	}

	void directs (string _output) {
		exec("rm -r " + _output + "720");
		exec("rm -r " + _output + "360");
		exec("rm -r " + _output + "240");

		exec("mkdir " + _output + "720");
		exec("mkdir " + _output + "360");
		exec("mkdir " + _output + "240");
	}

	int convertVideo(int _time, string path, string output){
		
		directs (output);
		string command;
		const char * _c;

		command = "../app/ffprobe -show_format '" + path + "' | sed -n '/duration/s/.*=//p'";
		_c = command.c_str();

		string _duration = exec(_c);
		float duration = ::atof(_duration.c_str());
		float temp = duration / _time;
		int chunks = int(temp + 1);

		command = "../app/ffmpeg -i '" + path + "' -r 1 -t 1 -ss 00:00:05 " + output + "preview.jpeg";
		_c = command.c_str();
		exec(_c);	

		for (int i = 0; i < chunks; i++) {
			command = "../app/ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i '" + path + "' -qscale 1 -s 320x240 -ar 22050 -b 800k -f mp4 -strict -2 -c:a aac " + output + "240/" + to_string(i) + ".mp4";
			_c = command.c_str();
			exec(_c);
		}

		for (int i = 0; i < chunks; i++) {
			command = "../app/ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i '" + path + "' -qscale 1 -s 640x360 -ar 22050 -b 800k -f mp4 -strict -2 -c:a aac " + output + "360/" + to_string(i) + ".mp4";
			_c = command.c_str();
			exec(_c);
		}

		for (int i = 0; i < chunks; i++) {
			command = "../app/ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i '" + path + "' -qscale 1 -s 1280x720 -ar 22050 -b 800k -f mp4 -strict -2 -c:a aac " + output + "720/" + to_string(i) + ".mp4";
			_c = command.c_str();
			exec(_c);
		}

		return chunks;
	}
}