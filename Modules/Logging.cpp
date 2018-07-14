#include "Logging.h"
#include "string.h"
#include "fstream"

Logging::Logging() {
}

Logging::Logging(char *	path) {
	this->setPath(path);
}

Logging::~Logging() {
	if (this->path != nullptr){
		delete this->path;
	}
	
}

int Logging::setPath(char* path) {
	// if this path is valid
	// if this path exist
	char* tmp = new char[strlen(path)];
	this->path = tmp;
	return 0;
}

int Logging::getPath(char* path) {
	if (this->path != nullptr) {
		strcpy_s(path, strlen(path),this->path);
		return 0;
	}
	else {
		return 1;
	}
}

int Logging::setDebugLevel(LOG_LEVEL level) {
	this->level = level;
	return 0;
}

LOG_LEVEL Logging::getDebugLevel() {
	return this->level;
}

template <class T>
void Logging::log(T parameter){
	using namespace std;
	ofstream ofs=ofstream(this->path, ios::app);	
	ofs << parameter << endl;
}
template <class T>
void Logging::info(T parameter) {

}
template <class T>
void Logging::warning(T parameter){
	
}
template <class T>
void Logging::critical(T parameter) {

}




























