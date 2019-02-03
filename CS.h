#ifndef CS_H
#define CS_H

#include <Windows.h>
#include <tlhelp32.h>

#include <iostream>

namespace CS {
	extern HANDLE csHandler;
	extern DWORD clientDll;
	extern DWORD hwDll;
	extern DWORD particleDll;

	void Setup();

	struct Offsets {
		DWORD EntityList = 0x011588;
		DWORD InCross = 0x124224;
		DWORD SetAngles = 0x1087B84;
		DWORD LocalPlayer = 0x1087ACC;
		DWORD WeaponBase = 0x1092FC0;
		DWORD ViewMatrix = 0xEC6460;
	};
	struct EntityList {
		int entityIndex;
		int alive;
		float position[3];
		int Dormant;
		int index = 0;
		Offsets offsets;

		void ReadEntity(int i) {
			index = i;
			DWORD entityloop = 0x28;
			DWORD structSize = 0xC + (0x28 * i);
			DWORD EntityPointer;
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.EntityList), &EntityPointer, sizeof(int), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(EntityPointer + (structSize)), &alive, sizeof(int), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(EntityPointer + (structSize)+0xC), &Dormant, sizeof(int), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(EntityPointer + (structSize)+0x10), &position, sizeof(position), 0);
		}
	};
	struct LocalPlayer {
		int health;
		float position[3];
		int alive;
		float viewAngles[3];
		Offsets offsets;
		char weapon[10];
		float ViewMatrix[4][4];
		int weaponId;

		void Read() {
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.LocalPlayer), &health, sizeof(int), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.LocalPlayer + 0x4EC), &alive, sizeof(int), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.LocalPlayer + 0xDC), &position, sizeof(position), 0);
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.SetAngles), &viewAngles, sizeof(viewAngles), 0);
			ReadWeapon();
			ReadViewMatrix();
		}

		void ReadViewMatrix() {
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.ViewMatrix), &ViewMatrix, sizeof(ViewMatrix), 0);
		}

		void ReadWeapon() {
			ReadProcessMemory(csHandler, (PBYTE*)(hwDll + offsets.WeaponBase), &weaponId, sizeof(weaponId), 0);
		}

		void SetAngles(float *angles) {
			WriteProcessMemory(CS::csHandler, (PBYTE*)(CS::hwDll + offsets.SetAngles), angles, 8, 0);
		}
	};

}


#endif