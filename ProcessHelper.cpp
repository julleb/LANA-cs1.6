#include "ProcessHelper.h"

namespace ProcessHelper {
	DWORD GetDLLAddress(DWORD pid, WCHAR *DLLName) {
		DWORD moduleBase = 0;
		HANDLE Snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
		if (Snap != INVALID_HANDLE_VALUE) {
			MODULEENTRY32 moduleEntry;
			moduleEntry.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(Snap, &moduleEntry)) {
				do {
					if (wcscmp(moduleEntry.szModule, DLLName) == 0) {
						moduleBase = (DWORD)moduleEntry.modBaseAddr;
						break;
					}
				} while (Module32Next(Snap, &moduleEntry));
			}
			CloseHandle(Snap);
			return moduleBase;
		}
	}

	DWORD GetPidOfWindow(const char *gamewindow) {
		DWORD pid = 0;
		HWND hwnd = FindWindowA(0, gamewindow);
		GetWindowThreadProcessId(hwnd, &pid);
		return (DWORD)pid;
	}

	HANDLE GetHandler(DWORD pid) {
		HANDLE ProcessHandler = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (!ProcessHandler) {
			std::cout << "cannot find game.." << std::endl;
			return 0;
		}
		return ProcessHandler;
	}
}
