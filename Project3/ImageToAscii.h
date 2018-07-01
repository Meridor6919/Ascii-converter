#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>

#pragma comment (lib,"Gdiplus.lib")

class ImageToAscii
{
	int image_x;
	int image_y;
	std::wstring image_path;

	int ascii_x;
	int ascii_y;
	std::string ascii_path;

	std::string ascii_chars;//from brightest to darkest

public:
	ImageToAscii(bool init);
	~ImageToAscii();
	void Conversion();
	bool Init();
	float Brightness(Gdiplus::Color color);
};