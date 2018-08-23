#include "LAN.h"
#include "iostream"
#include "timmer.h"

int main() {
	LANServer s("127.0.0.1",9433);
	s.enterMessageLoop();
	std::cin.get();
}