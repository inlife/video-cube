#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
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

void directs () {
	system("rm -r 720");
	system("rm -r 360");
	system("rm -r 240");

	system("mkdir 720");
	system("mkdir 360");
	system("mkdir 240");
}

bool convertVideo(int _time, string path, string output){
	
	directs ();
	string command;
	const char * _c;

	command = "./ffprobe -show_format " + path + " | sed -n '/duration/s/.*=//p'";
	_c = command.c_str();

	string duration = exec(_c);
	cout << duration << endl;
	float temp = stof(duration) / _time;
	cout << temp << endl;
	int chunks = int(temp + 1);
	cout << chunks << endl;

	command = "./ffmpeg -i " + path + " -r 1 -t 1 -ss 00:00:05 preview.jpeg";
	_c = command.c_str();
	system(_c);	

	for (int i = 0; i < chunks; i ++) {
		command = "./ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i " + path + " -qscale 1 -s 320x240 -vcodec mpeg4 -acodec ac3 " + output + "240/" + to_string(i) + ".mp4";
		_c = command.c_str();
		system(_c);
	}

	for (int i = 0; i < chunks; i ++) {
		command = "./ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i " + path + " -qscale 1 -s 640x360 -vcodec mpeg4 -acodec ac3 " + output + "360/" + to_string(i) + ".mp4";
		_c = command.c_str();
		system(_c);
	}

	for (int i = 0; i < chunks; i ++) {
		command = "./ffmpeg -ss " + to_string(i * _time) + " -t " + to_string(_time) +  " -i " + path + " -qscale 1 -s 1280x720 -vcodec mpeg4 -acodec ac3 " + output + "720/" + to_string(i) + ".mp4";
		_c = command.c_str();
		system(_c);
	}

	return true;
}