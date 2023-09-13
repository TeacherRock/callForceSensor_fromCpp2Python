#define 	DEBUGSS	0

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <thread>

#ifdef __cplusplus
extern "C" {
#endif
	void addThread_ForceSensor(int);
	__declspec(dllexport) unsigned short* getForceData();
#ifdef __cplusplus
}
#endif

int setComAttr(HANDLE);
void getForceSensor(HANDLE, unsigned short*);
void iniForceSensor();