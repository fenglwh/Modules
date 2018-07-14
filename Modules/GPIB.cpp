//
// Created by Adair on 2018/6/15.
//
#include "GPIB.h"
#include "iostream"
GPIB::GPIB() :m_viSession(0), m_ViStatus(0), m_vistr(0) {


}

GPIB::~GPIB() {

}

int GPIB::OpenDM() {
	return (VI_SUCCESS == viOpenDefaultRM(&m_viSession));
}
// I found these things will cuz issues, then I toggled these line for further use
// std::vector<char[256]> GPIB::listResource() {
// 	std::vector<char[256]> retVal;
// 	return retVal;
// }

int GPIB::Open(char *lpsession) {
	this->OpenDM();
	return (VI_SUCCESS == viOpen(m_viSession, lpsession, VI_NULL, VI_NULL, &m_vistr));
}

int GPIB::Write(char *command) {
	ViUInt32 iretcount = 0;
	char pBuffer[16640] = { 0 };
	strcpy_s(pBuffer, command);
	if (pBuffer[strlen(pBuffer)] != '\n') {
		strcat_s(pBuffer, "\n");
	}
	return (VI_SUCCESS == viWrite(m_vistr, (ViBuf)pBuffer, (unsigned int)strlen(pBuffer), &iretcount));
}

int GPIB::Read(ViBuf lpVisaString, unsigned int nBufCount) {
	ViUInt32 vicount = 0;
	return (VI_SUCCESS == viRead(m_vistr, lpVisaString, nBufCount, &vicount));
}

int GPIB::Query(char *command, ViBuf retVal, unsigned int nBufCount) {
	if (this->Write(command)) {
		return this->Read(retVal, nBufCount);
	}
	else {
		return _VI_ERROR;
	}
}

int GPIB::Close() {
	return  viClose(m_vistr) && viClose(m_viSession);
}

