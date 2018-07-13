#pragma once
#include"windows.h"
#include "vector"

bool exist();

bool isdir();

bool isfile();

bool makedir();

bool makedirs();

bool deleteFile();

bool deleteDir();

struct DirWalk{
	char dir[256];
	std::vector<char[256]> dirs;
	std::vector<char[256]> files;
};

DirWalk walk(char * path);

std::vector<char[256]> split( char* path) {
	
}