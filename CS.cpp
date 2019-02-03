#include "CS.h"
#include "ProcessHelper.h"

namespace CS {
	
	int AMOUNT_OF_ENTITY = 30;
	HANDLE csHandler;
	DWORD clientDll;
	DWORD hwDll;
	DWORD particleDll;

	void Setup() {
		DWORD pid = ProcessHelper::GetPidOfWindow("Counter-Strike");
		csHandler = ProcessHelper::GetHandler(pid);
		if (csHandler == 0) {
			getchar();
			return;
		}
		clientDll = ProcessHelper::GetDLLAddress(pid, L"client.dll");
		hwDll = ProcessHelper::GetDLLAddress(pid, L"hw.dll");
		particleDll = ProcessHelper::GetDLLAddress(pid, L"particleman.dll");
	}
}