#pragma once
#pragma warning(disable : 4996)
#pragma comment (lib,"Gdiplus.lib")

#include "Sprite.h"
#include "Graphics.h"
#include "Window.h"
#include <string>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>



class AsciiWindow {

	Sprite *window_image, *picture;
	Sprite *scroll_image_width, *scroll_image_height;
	int image_width;
	int image_height;
	int ascii_width;
	int ascii_height;
	std::string AsciiCharacters;
	ID3DXFont *Font1, *Font2, *Font3;
	RECT FontRect1, FontRect2, FontRect3;
	char FileName[MAX_PATH];
	Graphics *GraphicsDevice;
	bool button1_pressed;
	bool button2_pressed;

public:

	AsciiWindow(HWND MainWindowHwnd);
	void Main();
	void DragAndDropImage(HDROP drop);
	void Scroll(POINT cursor_pos, RAWINPUT* input);
	void ManualSizeChange(POINT cursor_pos, RAWINPUT* input);
	void ImagePath(POINT cursor_pos, RAWINPUT* input);
	void Convert(POINT cursor_pos, RAWINPUT* input);
	void Conversion(WCHAR* image_path, std::string ascii_path);
	void ChangeCharacters(RAWINPUT* input);
};
