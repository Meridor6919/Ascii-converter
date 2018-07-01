#pragma once
#include <windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR Title, int Width, int Height, HWND &hwnd, int Xpos = 0, int Ypos = 0);
bool InitializeInput();
RAWINPUT* GetInput(RAWINPUT* input, bool save);