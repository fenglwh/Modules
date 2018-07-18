#include "timmer.h"
void sleep_unix(unsigned const int millisecond) {
	timeval timeout;
	timeout.tv_sec = millisecond / 1000;
	timeout.tv_usec =millisecond % 1000*1000;
	::select(0, NULL, NULL, NULL, &timeout);
	return;
}
void sleep_windows(unsigned const int millisecond) {
	timeBeginPeriod(1);
	Sleep(millisecond);
	DWORD dwTime = ::timeGetTime();
	timeEndPeriod(1);
}

