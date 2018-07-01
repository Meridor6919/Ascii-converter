#include "Window.h"

bool InitializeInput()
{
	RAWINPUTDEVICE Input[2];

	//keyboard
	Input[0].usUsagePage = 0x01;
	Input[0].usUsage = 0x06;
	Input[0].dwFlags = 0;
	Input[0].hwndTarget = 0;
	//mouse
	Input[1].usUsagePage = 0x01;
	Input[1].usUsage = 0x02;
	Input[1].dwFlags = 0;
	Input[1].hwndTarget = 0;
	if (!RegisterRawInputDevices(Input, 2, sizeof(Input[0])))
		return false;
	return true;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_INPUT:
	{
		UINT dwSize;
		
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT *raw = (RAWINPUT*)lpb;
		GetInput(raw, true);
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR Title, int Width, int Height, HWND &hwnd, int Xpos, int Ypos)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = ClassName;

	RegisterClassEx(&wc);
	RECT wr = { 0, 0, Width, Height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hwnd = CreateWindowEx(NULL, ClassName, Title, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, Xpos, Ypos, wr.right - wr.left, wr.bottom - wr.top, 0, 0, hInstance, 0);

	ShowWindow(hwnd, nCmdShow);
	return true;
}
RAWINPUT* GetInput(RAWINPUT* input, bool save)
{
	static RAWINPUT* current_input;
	if (save)
		current_input = input;
	
	return current_input;
}