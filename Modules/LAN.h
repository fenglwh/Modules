#pragma once
#include <stdio.h>  
#include <winsock2.h>  
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")  
//#include<sys/socket.h>
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
	Buffer load();
};

class SockBase {
public:
	SOCKET socketNum;
	int timeout;
	char ip[256];
	short port;
	int family = AF_INET;
	int send(const char * data, int length);
	int send(Buffer);
	int recv(char * data, int &length);
	Buffer recv();
	int sendto(char* data,int length);
	int sendto(Buffer buf);
	int recvfrom(char*data ,int length);
	Buffer recvfrom();
	sockaddr_in makeAddr();
};

class LANClient:SockBase {
public:
	std::vector<Buffer> inBuffer;
	std::vector<Buffer> outBuffer;
	std::vector<void*> addressToFree;

	LANClient();
	LANClient(char* ip, int port,int family=AF_INET);
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


