#pragma once
#include "visatype.h"
#include "visa.h"
#include <stdarg.h>
#include "vector"
#include "map"
#include "stdlib.h"
#pragma comment (lib,"C:\\Program Files\\IVI Foundation\\VISA\\Win64\\Lib_x64\\msc\\visa32.lib")
#pragma comment (lib,"C:\\Program Files\\IVI Foundation\\VISA\\Win64\\Lib_x64\\msc\\visa64.lib")
#pragma comment (lib,"C:\\Program Files\\IVI Foundation\\VISA\\Win64\\Lib_x64\\msc\\nivisa64.lib")

class GPIB
{
public:

	GPIB();
	~GPIB();
	//    std::vector<char[256]> listResource();
	int Open(char * lpsession);

	int Write(char * command);
	int Read(ViBuf retVal, unsigned int nBufCount);
	int Query(char * command, ViBuf retVal, unsigned int nBufCount);
	int Close();

private:
	int OpenDM();
	static bool DMOpend;
	ViSession m_viSession;
	ViStatus  m_ViStatus;
	ViSession m_vistr;
};








