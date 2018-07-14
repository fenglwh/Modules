#include "LAN.h"

SockData SockData::parse(byte* data,int length) {
	SockData retVal;
	int pos = 0;
	retVal.type = (SOCK_MESSAGE_TYPE)(data[0] * 256 + data[1]);
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

Buffer SockData::load() {
	Buffer retVal;
	retVal.data[0] = (byte)(0xff & int(this->type));
	retVal.data[1] = (byte)((0xff00 & int(this->type)) >> 8);
	retVal.data[2] = (byte)(0xff & this->id);
	retVal.data[3] = (byte)((0xff00 & this->id) >> 8);
	retVal.data[4] = (byte)((0xff0000 & this->id) >> 16);
	retVal.data[5] = (byte)((0xff000000 & this->id) >> 24);
	retVal.data[6] = (byte)(0xff & this->length);
	retVal.data[7] = (byte)((0xff00 & this->length) >> 8);
	retVal.data[8] = (byte)((0xff0000 & this->length) >> 16);
	retVal.data[9] = (byte)((0xff000000 & this->length) >> 24);
	for (unsigned int i = 10; i < 10 + this->length; i++) {
		retVal.data[i] = this->data[i - 10];
	}
	retVal.length = 10 + this->length;
	return retVal;
}

int SockBase::send(const char * data, int length) {
	return ::send(this->socketNum, data, length,0);
}

int SockBase::send(Buffer buf) {
	return ::send(this->socketNum, buf.data, buf.length,0);
}

int SockBase::recv(char * data, int &length) {
	return ::recv(this->socketNum, data, length, 0);
}

int SockBase::recv(Buffer buf) {
	
}


LANServer::LANServer(){

}

LANServer::LANServer(char* ip, int port) {

}

LANServer::~LANServer() {
	for (void* add : this->addressToFree) {
		delete add;
	}
}

int LANServer::enterMessageLoop() {
	return 1;
}

int LANServer::getClientNum() {
	return 0;
}


LANClient::LANClient() {

}

LANClient::LANClient(char* ip, int port) {
	strcpy_s(this->ip, ip);
	this->port=port;
}

LANClient::~LANClient() {
	for (void* add : this->addressToFree) {
		delete add;
	}

}

int LANClient::connect() {
	this->socketNum = socket(AF_INET, SOCK_STREAM, 0);
	return ::connect(this->socketNum,(sockaddr *)&this->makeAddr(),sizeof(sockaddr));
}

int LANClient::disconnect() {
	return ::closesocket(this->socketNum);
}




int LANClient::read() {

	this->outBuffer.insert(this->outBuffer.end(),SockData))
}

int LANClient::write() {
}

int LANClient::query() {

}

sockaddr_in SockBase::makeAddr() {
	sockaddr_in sock = sockaddr_in();
	sock.sin_family= this->family;
	inet_pton(AF_INET,this->ip,&sock.sin_addr.s_addr);
	sock.sin_port = htons(this->port);
	return sock;
}








