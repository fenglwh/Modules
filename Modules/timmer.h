#pragma once
#include <winsock2.h>  
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")  

#if defined(__linux__) || defined(__unix__)
#define sleep sleep_unix
#elif defined(_WIN32)
#define sleep sleep_windows
#pragma comment(lib,"Winmm.lib")
#endif // 
#include "stdarg.h"
#include "time.h"

void sleep_unix(unsigned const int millisecond);
void sleep_windows(unsigned const int millisecond);




class Timmer {
	// should be a powerful class
	// abilities:
	//   able to record a time
	//   able to cauculate time such as can calculate the delta;
	//   able to fmt time and parse time struct, such as timestamp, and ascii
	//   able to exchange data with other time strut, such as time_t, tm

	time_t time_start;
	tm currenttime;
	tm now();
	time_t time_stamp();
	

};