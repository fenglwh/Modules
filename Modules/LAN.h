#pragma once
#include <stdio.h>  
#include <winsock2.h>  
#pragma comment(lib,"ws2_32.lib")  
#include "vector"

enum SOCK_MESSAGE_TYPE {
	aa = 1,
};


struct Buffer {
	char data[102400]="";
	int length=0;
};


struct SockData{
	//big endian
	SOCK_MESSAGE_TYPE type;
	unsigned int id;
	unsigned int length;
	byte data[102400];

	SockData parse(byte*,int length=0);
	Buffer load();
};

class SockBase {
	int socketNum;
	int timeout;
	char ip[256];
	short port;
	int family = 0;

	int send();
	int recv();
	sockaddr_in makeAddr();
};

class LANClient:SockBase {
	std::vector<Buffer> inBuffer;
	std::vector<Buffer> outBuffer;
	std::vector<void*> addressToFree;

	LANClient();
	LANClient(char* ip, int port);
	~LANClient();

	int connect();
	int disconnect();
	int read();
	int write();
	int query();
	int heartBeat();


};

class LANServer {
	std::vector<LANClient> clients;
	std::vector<void*> addressToFree;

	LANServer();
	LANServer(char* ip, int port);
	~LANServer();

	int enterMessageLoop();
	int getClientNum();
	int onMessage0();
};


