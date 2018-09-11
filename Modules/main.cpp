#include "LAN.h"
#include "iostream"
#include "timmer.h"
int main() {
	//LANServer s("127.0.0.1",9433);
	//std::cout << "quit main loop, return value is:"<<s.enterMessageLoop()<<std::endl;
	//std::cin.get();


	SockData data;
	data.type = SOCK_MESSAGE_TYPE::heartBeat;
	data.id = 20;
	strcpy(data.data, "I like you very much");
	data.length = strlen(data.data);
	LANClient c("127.0.0.1", 9433);
	c.connect();
	c.send(data);

	



}