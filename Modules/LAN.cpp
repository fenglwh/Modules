#include "LAN.h"
#include "iostream"

Buffer::Buffer(int length) {
	this->data = new char[length];
}


Buffer::~Buffer(){
	delete data;
}

SockData::SockData(int length) {
	this->data = new char[length];
}


int SockData::loadThis(char* data, int length) {
	int pos = 0;
	this->type = (SOCK_MESSAGE_TYPE)((unsigned char)data[1] * 256 + (unsigned char)data[0]);
	this->id = data[2] & 0xFF;
	this->id |= ((data[3] << 8) & 0xFF00);
	this->id |= ((data[4] << 16) & 0xFF0000);
	this->id |= ((data[5] << 24) & 0xFF000000);
	this->length = data[6] & 0xFF;
	this->length |= ((data[7] << 8) & 0xFF00);
	this->length |= ((data[8] << 16) & 0xFF0000);
	this->length |= ((data[9] << 24) & 0xFF000000);
	for (unsigned int i = 10; i < 10 + this->length; i++) {
		this->data[i - 10] = data[i];
	}
	return 1;
}

int SockData::loadThis(Buffer buf) {
	int pos = 0;
	this->type = (SOCK_MESSAGE_TYPE)((unsigned char)data[1] * 256 + (unsigned char)data[0]);
	this->id = buf.data[2] & 0xFF;
	this->id |= ((buf.data[3] << 8) & 0xFF00);
	this->id |= ((buf.data[4] << 16) & 0xFF0000);
	this->id |= ((buf.data[5] << 24) & 0xFF000000);
	this->length = buf.data[6] & 0xFF;
	this->length |= ((buf.data[7] << 8) & 0xFF00);
	this->length |= ((buf.data[8] << 16) & 0xFF0000);
	this->length |= ((buf.data[9] << 24) & 0xFF000000);
	for (unsigned int i = 10; i < 10 + this->length; i++) {
		this->data[i - 10] = buf.data[i];
	}
	return 1;
}


SockData SockData::load(char* data,int length) {
	SockData retVal;
	int pos = 0;
	retVal.type = (SOCK_MESSAGE_TYPE)((unsigned char)data[1] * 256 + (unsigned char)data[0]);
	retVal.id = data[2] & 0xFF;
	retVal.id |= ((data[3] << 8) & 0xFF00);
	retVal.id |= ((data[4] << 16) & 0xFF0000);
	retVal.id |= ((data[5] << 24) & 0xFF000000);
	retVal.length = data[6] & 0xFF;
	retVal.length |= ((data[7] << 8) & 0xFF00);
	retVal.length |= ((data[8] << 16) & 0xFF0000);
	retVal.length |= ((data[9] << 24) & 0xFF000000);
	for (unsigned int i = 10; i < 10 + retVal.length; i++) {
		retVal.data[i - 10] = data[i];
	}
	return retVal;
}

Buffer SockData::toBuffer() {
	Buffer retVal = {};
	retVal.data[0] = (char)(0xff & int(this->type));
	retVal.data[1] = (char)((0xff00 & int(this->type)) >> 8);
	retVal.data[2] = (char)(0xff & this->id);
	retVal.data[3] = (char)((0xff00 & this->id) >> 8);
	retVal.data[4] = (char)((0xff0000 & this->id) >> 16);
	retVal.data[5] = (char)((0xff000000 & this->id) >> 24);
	retVal.data[6] = (char)(0xff & this->length);
	retVal.data[7] = (char)((0xff00 & this->length) >> 8);
	retVal.data[8] = (char)((0xff0000 & this->length) >> 16);
	retVal.data[9] = (char)((0xff000000 & this->length) >> 24);
	for (unsigned int i = 10; i < 10 + this->length; i++) {
		retVal.data[i] = this->data[i - 10];
	}
	retVal.length = 10 + this->length;
	return retVal;
}

int SockData::bufferLength() {
	return 10 + this->length;
}

int SockBase::send(const char * data, int length) {
	return ::send(this->socketNum, data, length,0);
}

int SockBase::send(Buffer buf) {
	return ::send(this->socketNum, buf.data, buf.length,0);
}

int SockBase::send(SockData sockData) {
	return this->send(sockData.toBuffer());
}

int SockBase::recv(char * data, int length) {
	return ::recv(this->socketNum, data, length, 0);
}

SockData SockBase::recv() {
	SockData socktmp = {};
	Buffer buf={};
	char data[10240] = {};
	int ret_val=::recv(this->socketNum, data, 10240, 0);
	if (ret_val == 0) {
		socktmp.type = SOCK_MESSAGE_TYPE::DISCONNECT;
		std::cout << "disconnect!"<<ret_val << std::endl;
	}
	else {
		socktmp.type = (SOCK_MESSAGE_TYPE)((unsigned char)data[1] * 256 + (unsigned char)data[0]);
		socktmp.id = data[2] & 0xFF;
		socktmp.id |= ((data[3] << 8) & 0xFF00);
		socktmp.id |= ((data[4] << 16) & 0xFF0000);
		socktmp.id |= ((data[5] << 24) & 0xFF000000);
		socktmp.length = data[6] & 0xFF;
		socktmp.length |= ((data[7] << 8) & 0xFF00);
		socktmp.length |= ((data[8] << 16) & 0xFF0000);
		socktmp.length |= ((data[9] << 24) & 0xFF000000);
		for (unsigned int i = 10; i < 10 + socktmp.length; i++) {
			socktmp.data[i - 10] = data[i];
		}
	}
	return socktmp;
}


//int SockBase::sendto(char* data, int length) {
//
//}
//
//int SockBase::sendto(Buffer buf) {
//
//}
//
//int SockBase::recvfrom(char* data, int length) {
//
//}
//
//Buffer SockBase::recvfrom() {
//
//}

int SockBase::getIP(char * IP) {
	inet_ntop(AF_INET,(void*)&this->sockEntity.sin_addr, IP,16);
	return 0;
}

std::string SockBase::getIP() {
	return std::string();
}

int SockBase::getPort() {
	return ntohs(this->sockEntity.sin_port);
}

int SockBase::getFamily() {
	return this->sockEntity.sin_family;
}

int SockBase::setIP(const char* ip) {
	inet_pton(AF_INET, ip, (void*)&this->sockEntity.sin_addr);
	return 0;
}

int SockBase::setIP(std::string ip) {
	inet_pton(AF_INET, ip.c_str(), (void*)&this->sockEntity.sin_addr);
	return 0;
}

int SockBase::setPort(int port) {
	this->sockEntity.sin_port = htons(port);
	return 0;
}

int SockBase::setFamily(int family) {
	this->sockEntity.sin_family = family;
	return 0;
}

LANClient::LANClient() {

}

LANClient::LANClient(const LANClient& other) {
	this->sockEntity = other.sockEntity;
	this->socketNum = other.socketNum;
}

LANClient::LANClient(const char* ip, int port,int family) {
	inet_pton(AF_INET, ip, (void*)&this->sockEntity.sin_addr);
	this->sockEntity.sin_port = htons(port);
	this->sockEntity.sin_family = family;
}

LANClient::~LANClient() {
	for (void* add : this->addressToFree) {
		delete add;
	}
	if (this->connected==1) {
		this->disconnect();
	}
}

int LANClient::connect() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	this->socketNum = socket(AF_INET, SOCK_STREAM, 0);
	int ret_val= ::connect(this->socketNum,(sockaddr*)&this->sockEntity,sizeof(sockaddr_in));
	if (ret_val == 0) {
		this->connected = 1;
	}
	this->workloopThread = std::thread(&LANClient::workLoop,this);
	//this->workloopThread.detach();
	return ret_val;
}

int LANClient::disconnect() {
	int retVal= ::closesocket(this->socketNum);
	WSACleanup();
	this->connected = 0;
	this->workloopThread.join();
	return retVal;
}

int LANClient::bufferRead() {
	// recv to buffer
	SockData socktmp;
	socktmp=this->recv();
	this->inBuffer[socktmp.id] = socktmp.toBuffer();
	//this part is use to test the read
	//std::cout << "message:";
	//for (int i=0; i < buffertmp.length; i++) {
	//	std::cout << (unsigned int)(unsigned char)(buffertmp.data[i])<<" ";
	//}
	//std::cout << std::endl;
	return 1;
}

int LANClient::bufferWrite() {
	// buffer send to peer
	this->send(this->outBuffer.front());
	this->outBuffer.pop_front();
	return 1;
}


SockData LANClient::read(unsigned int id){ 
	SockData retVal = {};
	if (this->inBuffer.count(id) > 0) {
		retVal.loadThis(this->inBuffer[id]);
		this->inBuffer.erase(id);
	}
	return retVal;
}

int LANClient::write(const char* command) {
	SockData socktmp;
	socktmp.type = SOCK_MESSAGE_TYPE::textMessage;
	socktmp.id = this->messageId;
	this->messageId++;
	socktmp.length = strlen(command);
	strcpy_s(socktmp.data, 10240,command);
	this->outBuffer.push_back(socktmp.toBuffer());
	return socktmp.id;
}
int LANClient::write(SockData socktmp) {
	this->outBuffer.push_back(socktmp.toBuffer());
	return socktmp.id;
}

SockData LANClient::query(const char* command) {
	return this->read(this->write(command));
}

int LANClient::workLoop() {
	fd_set rfds, wfds;
	timeval timeout = {0,50};
	this->workLoopRuning = 1;
	while (this->connected==1) {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(this->socketNum, &rfds);
		FD_SET(this->socketNum, &wfds);
		switch (select(0, &rfds, &wfds, NULL, &timeout)) {
		case 0:
			continue;
		case -1:
			this->workLoopRuning = 0;
			return 255;
		default:
			if (FD_ISSET(this->socketNum, &rfds)) {
				this->bufferRead();
			}
			if (FD_ISSET(this->socketNum, &wfds) && this->outBuffer.size()>0) {
				this->bufferWrite();
			}
		}
	}
	this->workLoopRuning = 0;
	return 0;
}

int LANClient::heartBeat() {
	SockData socktmp;
	socktmp.type = SOCK_MESSAGE_TYPE::heartBeat;
	socktmp.id = 0;
	socktmp.length = 0;
	return this->write(socktmp);
}

int LANClient::clearBuffer() {
	this->inBuffer.clear();
	this->outBuffer.clear();
	return 1;
}




LANServer::LANServer() {

}

LANServer::LANServer(const char* ip, int port, int family) {
	this->sockEntity.sin_addr.s_addr = inet_addr(ip);
	inet_pton(AF_INET, ip, (void*)&this->sockEntity.sin_addr);
	this->sockEntity.sin_port = htons(port);
	this->sockEntity.sin_family = family;
}

LANServer::~LANServer() {
	for (void* add : this->addressToFree) {
		delete add;
	}
}

int LANServer::enterMessageLoop() {

	fd_set rfds, wfds;
	DWORD d;
	SockData sktmp;
	int i, rv, intTmp = sizeof(sockaddr_in);
	timeval timeout = { 0,50 };
	LANClient client=LANClient();
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	this->socketNum = socket(AF_INET, SOCK_STREAM, 6);
	::bind(this->socketNum, (sockaddr*)&this->sockEntity, sizeof(sockaddr_in));
	::listen(this->socketNum, 5);
	while (1) {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(this->socketNum, &rfds);
		FD_SET(this->socketNum, &wfds);
		if (this->connected) {
			FD_SET(client.socketNum, &rfds);
		}
		if (this->connected) {
			FD_SET(client.socketNum, &wfds);
		}
		switch (select(0, &rfds, &wfds, NULL, &timeout)) {
		case 0:
			continue;
		case -1:
			d = GetLastError();
			this->workLoopRuning = 0;
			return d;
		default:
			if (FD_ISSET(this->socketNum, &rfds)) {
				if (this->connected != 1) {
					intTmp = sizeof(sockaddr_in);
					client.socketNum = ::accept(this->socketNum, (sockaddr*)&(client.sockEntity), &intTmp);
					if (client.socketNum != INVALID_SOCKET) {
						std::cout << "connected" << std::endl;
						this->connected = 1;
					}
					else {
						std::cout << " invalid socket"<< rv << std::endl;
					}
				}
			}
			if (FD_ISSET(client.socketNum, &rfds)) {
				sktmp = client.recv();
				if (sktmp.type== SOCK_MESSAGE_TYPE::DISCONNECT) {
					::closesocket(client.socketNum);
					this->connected = 0;

					continue;
				}
				onMessage(sktmp);
			}
			if (FD_ISSET(client.socketNum, &wfds) && this->outBuffer.length > 0) {
				this->send(outBuffer);
			}
		}

	}


	WSACleanup();
	return 1;
}

int LANServer::getClientNum() {
	return 0;
}

int LANServer::onMessage(SockData data) {
	std::cout<< data.type<< std::endl;
	std::cout<< data.data<< std::endl;
	std::cout<< data.id<< std::endl;
	return 1;
}








