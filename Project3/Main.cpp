#pragma once
#include "Graphics.h"
#include "Sprite.h"
#include "Window.h"
#include "AsciiApi.h"

#pragma comment(lib, "D3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Dxguid.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RECT rect;
	HWND hwnd = GetDesktopWindow();
	GetWindowRect(hwnd, &rect);
	int X = rect.right - rect.left;
	int Y = rect.bottom - rect.top;

	HWND MainWindowHwnd;
	MSG msg;

	GenerateWindow(hInstance, nCmdShow, "WindowClass_1", "Ascii converter", 800, 600, MainWindowHwnd, (X-800)/2, (Y-600)/2);
	InitializeInput();
	AsciiWindow MainWindow(MainWindowHwnd);
	
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;

			else if (msg.message == WM_INPUT)
			{
				POINT info;
				
				GetCursorPos(&info);
				ScreenToClient(MainWindowHwnd, &info);

				MainWindow.Scroll(info, GetInput(0, 0));
				MainWindow.ManualSizeChange(info, GetInput(0, 0));
				MainWindow.ImagePath(info, GetInput(0, 0));
				MainWindow.Convert(info, GetInput(0, 0));
				MainWindow.ChangeCharacters(GetInput(0, 0));
			}
			else if (msg.message == WM_DROPFILES)
				MainWindow.DragAndDropImage((HDROP)msg.wParam);
		}
		else
			MainWindow.Main();	
	}
	return msg.wParam;
}