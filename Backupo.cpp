//// include the basic windows header file
// CTRL K + CTRL U eller CTRL C
//
//#include <windows.h>
//#include <windowsx.h>
//#include <iostream>
//
//#include <stdio.h>      /* printf, scanf, puts, NULL */
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>  
//
//#include "Radar.h"
//#include "CS.h"
//#include "Aimbot.h"
//
//
//#include <Dwmapi.h> 
//#include <TlHelp32.h>
//#pragma comment (lib, "Dwmapi.lib")
//
//void aimbot() {
//	CS::LocalPlayer LocalPlayer;
//	CS::EntityList EntityList;
//
//	Aimbot::FOV = 2.0f;
//	Aimbot::SMOOTH = 20;
//
//	float nearestFov = 999999.0f;
//	int nearestIndex = -1;
//	while (true) {
//		for (int i = 0; i < 30; ++i) {
//			LocalPlayer.Read();
//			EntityList.ReadEntity(i);
//
//			if (EntityList.alive != 3)continue;
//			if (EntityList.Dormant != 1) continue;
//			float fov = Aimbot::GetFOV(LocalPlayer.position, EntityList.position, LocalPlayer.viewAngles);
//			if (fov < nearestFov) {
//				nearestFov = fov;
//				nearestIndex = i;
//			}
//		}
//		if (GetAsyncKeyState(0x01)) {
//			EntityList.ReadEntity(nearestIndex);
//			if (Aimbot::GetFOV(LocalPlayer.position, EntityList.position, LocalPlayer.viewAngles) < Aimbot::FOV) {
//				Aimbot::aim(LocalPlayer, EntityList);
//			}
//		}
//		nearestIndex = -1;
//		nearestFov = 999999.0f;
//	}
//
//}
//
//void renderRadar(HWND hWnd) {
//	Radar::SetupDrawing(hWnd);
//	Radar::DrawRadar();
//
//	CS::LocalPlayer LocalPlayer;
//	CS::EntityList EntityList;
//
//	for (int i = 0; i < 30; i++) {
//		LocalPlayer.Read();
//		EntityList.ReadEntity(i);
//		if (EntityList.alive != 3)continue;
//		if (EntityList.Dormant != 1) continue;
//		int *position = Radar::GetEntityPositionInRadar(LocalPlayer.position, LocalPlayer.viewAngles[1], EntityList.position);
//		Radar::DrawEntity(position[0], position[1]);
//	}
//	Radar::EndDrawing(hWnd);
//}
//
//void createConsole()
//{
//	//Allocate a console so we can debugg!
//	AllocConsole();
//	freopen("CONOUT$", "wb", stdout);
//	freopen("CONOUT$", "wb", stderr);
//	freopen("CONIN$", "rb", stdin);
//	SetConsoleTitle(L"SUP GUYS");
//}
//
///*
//typedef struct _MARGINS {
//int cxLeftWidth;
//int cxRightWidth;
//int cyTopHeight;
//int cyBottomHeight;
//} MARGINS, *PMARGINS;
//*/
//
//// the WindowProc function prototype
//LRESULT CALLBACK WindowProc(HWND hWnd,
//	UINT message,
//	WPARAM wParam,
//	LPARAM lParam);
//
//// the entry point for any Windows program
//int WINAPI WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nCmdShow)
//{
//	// the handle for the window, filled by a function
//	HWND hWnd;
//	srand(time(NULL));
//	// this struct holds information for the window class
//	WNDCLASSEX wc;
//
//	// clear out the window class for use
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//	// fill in the struct with the needed information
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WindowProc;
//	wc.hInstance = hInstance;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//	wc.lpszClassName = L"WindowClass1";
//
//	// register the window class
//	RegisterClassEx(&wc);
//
//	HWND csHWND = FindWindow(NULL, L"Counter-Strike");
//	RECT csRECT;
//	GetClientRect(csHWND, &csRECT);
//	int heightCenter = csRECT.bottom / 2;
//	int widthCenter = csRECT.right / 2;
//
//	int widthOfWindow = 150;
//	int heightOfWindow = 150;
//
//
//	// create the window and use the result as the handle
//	hWnd = CreateWindowEx(NULL,
//		L"WindowClass1",    // name of the window class
//		L"Radar4TheWins",   // title of the window
//		WS_EX_TOPMOST | WS_POPUP,    // window style
//		widthCenter - widthOfWindow / 2,    // x-position of the window
//		heightCenter + heightCenter / 2,    // y-position of the window
//		150,    // width of the window
//		150,    // height of the window
//		NULL,    // we have no parent window, NULL
//		NULL,    // we aren't using menus, NULL
//		hInstance,    // application handle
//		NULL);    // used with multiple windows, NULL
//
//				  // display the window on the screen
//	SetWindowLong(hWnd, GWL_EXSTYLE, (int)GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
//	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
//	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
//	ShowWindow(hWnd, nCmdShow);
//
//
//
//	// enter the main loop:
//
//	// this struct holds Windows event messages
//	MSG msg;
//	//createConsole();
//	CS::Setup();
//	HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)aimbot, NULL, 0, NULL);
//	CloseHandle(thread);
//	// wait for the next message in the queue, store the result in 'msg'
//	while (true) {
//		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		if (msg.message == WM_QUIT)
//			break;
//
//		RECT rc;
//		GetClientRect(hWnd, &rc);
//		InvalidateRect(hWnd, &rc, TRUE);
//		Sleep(10);
//	}
//
//	// return this part of the WM_QUIT message to Windows
//	return msg.wParam;
//}
//
//// this is the main message handler for the program
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	const MARGINS  margin = { 0,0,100,100 };
//	// sort through and find what code to run for the message given
//	switch (message) {
//	case WM_PAINT:
//		//DwmExtendFrameIntoClientArea(hWnd, &margin);
//		renderRadar(hWnd);
//		break;
//		// this message is read when the window is closed
//	case WM_DESTROY:
//	{
//		// close the application entirely
//		PostQuitMessage(0);
//		return 0;
//	} break;
//	}
//
//	// Handle any messages the switch statement didn't
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
