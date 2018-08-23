#pragma once
#include <stdio.h>  
#include <winsock2.h>  
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")  
//#include<sys/socket.h>
#include "list"
#include "map"
#include "thread"
#include "string"
enum SOCK_MESSAGE_TYPE {
	init = 0,

	heartBeat=254,
	textMessage=255,
	UDP_ACK=256,
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
	char data[102400];
	int loadThis(char*, int length = 0);
	int loadThis(Buffer);
	SockData load(char*,int length=0);
	Buffer toBuffer();
	int bufferLength();
};

class SockBase {
public:
	SOCKET socketNum;
	int timeout=1200000;//ms
	sockaddr_in sockEntity;
	int send(const char * data, int length);
	int send(Buffer);
	int send(SockData);
	int recv(char * data, int length);
	Buffer recv();
	//int sendto(char* data,int length);
	//int sendto(Buffer buf);
	//int recvfrom(char*data ,int length);
	//Buffer recvfrom();
	int getIP(char *);
	std::string getIP();
	int getPort();
	int getFamily();
	int setIP(const char*);
	int setIP(std::string);
	int setPort(int);
	int setFamily(int);
};

class LANClient:public SockBase {
	
public:
	std::map<int,Buffer> inBuffer;
	std::list<Buffer> outBuffer;
	std::list<void*> addressToFree;
	int messageId = 1;
	int connected = 0;
	std::thread workloopThread;
	int workLoopRuning = 0;

	LANClient();
	LANClient(const LANClient&);
	LANClient(const char* ip, int port,int family=AF_INET);
	~LANClient();

	int connect();
	int disconnect();
	int bufferRead();
	int bufferWrite();
	

	SockData read(unsigned int id=0);
	int write(const char* command);
	int write(SockData);
	SockData query(const char* command);
	int workLoop();
	int heartBeat();
	int clearBuffer();
};

class LANServer:public SockBase {
public:
	std::list<void*> addressToFree;
	int workLoopRuning = 0;
	char inBuffer[102400];
	char outBuffer[102400];
	int inBufferLength=0;
	int outBufferLength = 0;
	int connected=0;
	LANServer();
	LANServer(const char* ip, int port, int family = AF_INET);
	~LANServer();

	int enterMessageLoop();
	int getClientNum();
	int onMessage(SockData data);
};


