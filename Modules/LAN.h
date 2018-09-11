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
	READ=1,
	WRITE=2,
	QUERY=3,
	READ_RESULT=4,
	QUERY_RESPONSE=5,
	DISCONNECT = 253,
	heartBeat=254,
	textMessage=255,
	UDP_ACK=256,
};


struct Buffer {
	Buffer(int length=102400);
	char * data;
	int length=0;
	~Buffer();
};


struct SockData{
	//big endian
	SockData(int length=102400);
	SOCK_MESSAGE_TYPE type;
	unsigned int id;
	unsigned int length;
	char * data;
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
	SockData recv();
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
	Buffer outBuffer = Buffer(102400);
	int connected=0;
	LANServer();
	LANServer(const char* ip, int port, int family = AF_INET);
	~LANServer();

	int enterMessageLoop();
	int getClientNum();
	int onMessage(SockData data);
};


