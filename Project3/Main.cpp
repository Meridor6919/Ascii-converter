#pragma once
#include "Graphics.h"
#include "Sprite.h"
#include "Window.h"
#include "AsciiApi.h"


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






















/*
#include "Hacks.h"
#include "NeuralNet.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <gdiplus.h>


int main()
{
/*
HBITMAP hbm;
BITMAP bm;
std::string path = "Bieg2.png";
hbm = (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
GetObject(hbm, sizeof(BITMAP), &bm);
OpenClipboard(NULL);
EmptyClipboard();
SetClipboardData(CF_BITMAP, hbm);
CloseClipboard();





BITMAP bm;
std::fstream fvar;
// get the device context of the screen
HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);
// and a device context to put it in
HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

int width = GetDeviceCaps(hScreenDC, HORZRES);
int height = GetDeviceCaps(hScreenDC, VERTRES);
BYTE* Byte = new BYTE[(4 * width * height)];
// maybe worth checking these are positive values
HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

// get a new bitmap
HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);


BITMAPINFOHEADER bmi = { 0 };
bmi.biSize = sizeof(BITMAPINFOHEADER);
bmi.biPlanes = 1;
bmi.biBitCount = 32;
bmi.biWidth = width;
bmi.biHeight = -height;
bmi.biCompression = BI_RGB;
bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;

GetDIBits(hMemoryDC, hBitmap, 0, height, Byte, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);


//50
int resolution_x = 100;
int resolution_y = 50;

int pixel_x = width / resolution_x;
int pixel_y = height / resolution_y;

int cursor_x = 0;
int cursor_y = 0;

int r = 0, g = 0, b = 0;


for (int y = 0; y < pixel_y; y++)
{
for (int x = 0; x < pixel_x; x++)
{

}
}




// clean up
DeleteDC(hMemoryDC);
DeleteDC(hScreenDC);


OpenClipboard(NULL);
EmptyClipboard();
SetClipboardData(CF_BITMAP, hBitmap);
CloseClipboard();

std::cin.get();
}
void ScreenCap()
{

}

//return ScreenData[4 * ((y*ScreenX) + x)]; B
//return ScreenData[4 * ((y*ScreenX) + x) + 1]; G
//return ScreenData[4 * ((y*ScreenX) + x) + 2]; R
//std::cout << "Bitmap: r: " << PosR(p.x, p.y) << " g: " << PosG(p.x, p.y) << " b: " << PosB(p.x, p.y) << "\n";




*/