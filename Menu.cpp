#include "Menu.h"

#include <vector>
#include <string>
#include "Config.h"
#include <iostream>
#include <sstream>
namespace Menu {

	bool showMenu = true;
	int positionX = 300;
	int positionY = 100;
	int width = 100;
	int height = 200;
	int x = positionX + 10;
	int y = positionY + 10;
	int stepSize = 20;

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 100));

	std::vector<LPCWSTR> options = {L"aim", L"fov", L"smooth", L"esp"};
	int option = 0;
	
	LPCWSTR toLPCWSTR(int value) {
		char buffer[512];
		sprintf(buffer, "%d", value);
		WCHAR wsz[64];
		swprintf(wsz, L"%S", buffer);
		return wsz;
	}
	LPCWSTR toLPCWSTR(float value) {
		char buffer[512];
		sprintf(buffer, "%.2f", value);
		WCHAR wsz[64];
		swprintf(wsz, L"%S", buffer);
		return wsz;
	}

	void drawOptions() {

		if (GetAsyncKeyState(VK_DOWN) & 1) {
			option++;
			if (option >= options.size()) option = 0;
		}
		if (GetAsyncKeyState(VK_UP) & 1) {
			option--;
			if (option < 0) option = options.size() - 1;
		}
		
		Drawer::DrawText(L">", positionX, y + (option*stepSize));
		for (int i = 0; i < options.size(); ++i) {
			Drawer::DrawText(options[i], x, y + (i*stepSize));
		}
	}

	void drawOptionsValue() {
		int tabSize = 60;
		int i = 0;
		Drawer::DrawText(toLPCWSTR(Config::config.aim), x + tabSize, y + (i*stepSize));
		i++;
		Drawer::DrawText(toLPCWSTR(Config::config.fov), x + tabSize, y + (i*stepSize));
		i++;
		Drawer::DrawText(toLPCWSTR(Config::config.smooth), x + tabSize, y + (i*stepSize));
		i++;
		Drawer::DrawText(toLPCWSTR(Config::config.esp), x + tabSize, y + (i*stepSize));
	}

	void changeOptionsValue() {
		if (GetAsyncKeyState(VK_LEFT) & 1) {
			if (option == 0) Config::config.aim = 0;
			if (option == 1) {
				Config::config.fov -= 0.05f;
				if (Config::config.fov <= 0.05f) Config::config.fov = 0.05f;
			}
			if (option == 2) {
				Config::config.smooth -= 1;
				if (Config::config.smooth <= 1) Config::config.smooth = 1;
			}
			if (option == 3) Config::config.esp = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1) {
			if (option == 0) Config::config.aim = 1;
			if (option == 1) {
				Config::config.fov += 0.05f;
				if (Config::config.fov >= 5) Config::config.fov = 5;
			}
			if (option == 2) {
				Config::config.smooth += 1;
				if (Config::config.smooth >= 100) Config::config.smooth = 100;
			}
			if (option == 3) Config::config.esp = 1;
			
		}
	}

	void drawMenu() {
		if (GetAsyncKeyState(VK_NEXT) & 1) {
			showMenu = !showMenu;
		}
		if (showMenu == false) return;

		Drawer::DrawFilledRectangle(brush, positionX, positionY, width, height);
		drawOptions();
		drawOptionsValue();
		changeOptionsValue();
	}



	void Draw() {
		drawMenu();
	}

	
}