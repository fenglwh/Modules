#include "LAN.h"
#include "iostream"

int main() {
	LANClient c("127.0.0.1",9433);
	std::cout << c.connect() << std::endl;;
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	c.heartBeat();
	Sleep(10000000);
	c.disconnect();
	std::cout << "finished" << std::endl;
	std::cin.get();
}