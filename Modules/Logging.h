#pragma once
enum LOG_LEVEL
{
	ALL = 0,
	INFO=1,
	Warning = 2,
	Critical=3,
};

class Logging {
private:
	LOG_LEVEL level;
	char * path;
public:
	Logging();
	Logging(char* path);
	//Logging(wchar_t * path);
	~Logging();

	int setPath(char* path);
	int getPath(char* path);
	int setDebugLevel(LOG_LEVEL level);
	LOG_LEVEL getDebugLevel();
	template <class T> 
	void log(T parameter);
	template <class T>
	void info(T parameter);
	template <class T>
	void warning(T parameter);
	template <class T>
	void critical(T parameter);

};