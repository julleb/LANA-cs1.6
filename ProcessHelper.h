#ifndef PROCESSHELPER_H
#define PROCESSHELPER_H

#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>

namespace ProcessHelper {
	DWORD GetDLLAddress(DWORD pid, WCHAR *DLLName);
	DWORD GetPidOfWindow(const char *gamewindow);
	HANDLE GetHandler(DWORD pid);
}



#endif