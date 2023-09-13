#include "ForceSensor.hpp"

unsigned short data[6] = { 0 };
//unsigned short inidata[6] = { 8122, 8200, 8613, 8280, 8351, 8296 }; 
// 2023/09/13 : 8122, 8200, 8613, 8280, 8351, 8296

int setComAttr(HANDLE fdc) {
	//===================== Input ======================

	//===================== Output =====================

	int				status;
	BOOL			success;
	COMMTIMEOUTS	timeouts;
	DCB				dcb;

	status = 0;

	timeouts.ReadIntervalTimeout = 1;
	timeouts.ReadTotalTimeoutMultiplier = 1;
	timeouts.ReadTotalTimeoutConstant = 1;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant = 1;

	SetCommTimeouts(fdc, &timeouts);		//  Setting the time-out of "Read Write"
	EscapeCommFunction(fdc, SETDTR);		// Set the Data Terminal Ready line

	// Get the current settings of the COMM port 
	success = GetCommState(fdc, &dcb);
	if (!success)
	{
		status = -1;
	}

	// Modify the baud rate, etc.
	dcb.BaudRate = 921600;
	dcb.ByteSize = (BYTE)8;
	dcb.Parity = (BYTE)NOPARITY;
	dcb.StopBits = (BYTE)ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;

	// Apply the new comm port settings
	success = SetCommState(fdc, &dcb);
	if (!success)
	{
		status = -2;
	}

	return (status);
};

void getForceSensor(HANDLE fdc, unsigned short* data_) {
	//===================== Input ======================

	//===================== Output =====================

	char		str[256];
	int			tick;
	DWORD n;
	while(TRUE) {
		// Request single data(second time)
		WriteFile(fdc, "R", 1, &n, 0);

		// Get single data
		n = 0;
		ReadFile(fdc, str, 27, &n, 0);

		sscanf_s(str, "%1d%4hx%4hx%4hx%4hx%4hx%4hx",
			&tick, &data_[0], &data_[1], &data_[2], &data_[3], &data_[4], &data_[5]);
	}
};

void addThread_ForceSensor(int comNo) {
	//===================== Input ======================

	//===================== Output =====================

	HANDLE		fdc;
	//char		fname[64];
	char		devname[64];  // COM number ex: "COM4"

	fdc = NULL;

	sprintf_s(devname, "COM%d", comNo);
	fdc = CreateFile(devname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	if (fdc == INVALID_HANDLE_VALUE) {
		// Not handle the COM
	}

	// Set baud rate and others parameters of COM port
	setComAttr(fdc);

	std::thread myThread(getForceSensor, fdc, data);
	myThread.detach();
	iniForceSensor();
}

__declspec(dllexport) unsigned short* getForceData() {
	return data;
}

void iniForceSensor() {
	std::cout << "Initializing thr Force Sensor !!" << std::endl;
	while (data[0] == 0 || data[1] == 0 || data[2] == 0  || data[3] == 0 || data[4] == 0 || data[5] == 0);

}