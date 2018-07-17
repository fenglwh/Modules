#include "LAN.h"
#include "iostream"

int main() {
	LANClient c = LANClient("127.0.0.1",9433);
	std::cout << c.connect() << std::endl;;
	c.send("12345678910", 11);
	c.send
	c.disconnect();
	std::cout << "finished" << std::endl;
	std::cin.get();
}