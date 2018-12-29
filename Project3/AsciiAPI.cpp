#include "AsciiApi.h"


AsciiWindow::AsciiWindow(HWND MainWindowHwnd)
{
	DragAcceptFiles(MainWindowHwnd, true);
	Gdiplus::GdiplusStartupInput gdiSI;
	ULONG_PTR ulong_ptr;
	Gdiplus::GdiplusStartup(&ulong_ptr, &gdiSI, 0);
	AsciiCharacters = "&0OYu^*',. ";

	GraphicsDevice = new Graphics();
	GraphicsDevice->InitGraphics(MainWindowHwnd, true);
	button1_pressed = false;
	button2_pressed = false;
	picture = nullptr;

	window_image = new Sprite(0, 0, 0);
	if (!window_image->InitSprite(GraphicsDevice->device, "interface.png", 800, 600))
		exit(0);
	scroll_image_width = new Sprite(280, 485, 0);
	if (!scroll_image_width->InitSprite(GraphicsDevice->device, "scroll.png", 18, 20))
		exit(0);
	scroll_image_height = new Sprite(700, 485, 0);
	if (!scroll_image_height->InitSprite(GraphicsDevice->device, "scroll.png", 18, 20))
		exit(0);

	SetRect(&FontRect1, 150, 523, 206, 537);
	SetRect(&FontRect2, 570, 523, 622, 537);
	SetRect(&FontRect3, 300, 523, 500, 550);
	D3DXCreateFontA(GraphicsDevice->device, 16, 8, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &Font1);
	D3DXCreateFontA(GraphicsDevice->device, 16, 8, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &Font2);
	D3DXCreateFontA(GraphicsDevice->device, 20, 10, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &Font3);
}
void AsciiWindow::Main()
{
	GraphicsDevice->Clear(D3DCOLOR_XRGB(255, 255, 255));
	GraphicsDevice->Begin();

	window_image->Draw();
	scroll_image_width->Draw();
	scroll_image_height->Draw();
	if (picture != nullptr)
	{
		picture->Draw();
		Font1->DrawTextA(0, (LPCSTR)std::to_string(ascii_width).c_str(), -1, &FontRect1, DT_RIGHT, D3DCOLOR_XRGB(0, 0, 0));
		Font2->DrawTextA(0, (LPCSTR)std::to_string(ascii_height).c_str(), -1, &FontRect2, DT_RIGHT, D3DCOLOR_XRGB(0, 0, 0));
		Font3->DrawTextA(0, (LPCSTR)AsciiCharacters.c_str(), -1, &FontRect3, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0));
	}
	GraphicsDevice->End();
	GraphicsDevice->Present();
}
void AsciiWindow::Scroll(POINT cursor_pos, RAWINPUT* input)
{
	if (input->data.mouse.ulButtons == 1 && cursor_pos.y<scroll_image_height->position.y + 20 && cursor_pos.y>scroll_image_height->position.y && cursor_pos.x > scroll_image_height->position.x && cursor_pos.x < scroll_image_height->position.x + 18)
		button1_pressed = true;
	else if (input->data.mouse.ulButtons == 1 && cursor_pos.y<scroll_image_width->position.y + 20 && cursor_pos.y>scroll_image_width->position.y && cursor_pos.x > scroll_image_width->position.x && cursor_pos.x < scroll_image_width->position.x + 18)
		button2_pressed = true;
	else if (input->data.mouse.ulButtons == 2)
	{
		button1_pressed = false;
		button2_pressed = false;
	}

	if (button1_pressed)
	{
		//weak
		scroll_image_height->position.x = cursor_pos.x;
		if (scroll_image_height->position.x < 516)
			scroll_image_height->position.x = 516;
		else if(scroll_image_height->position.x > 700)
			scroll_image_height->position.x = 700;
		if (picture != nullptr)
		{
			ascii_height = static_cast<float>(image_height) / 184.0f * static_cast<float>(scroll_image_height->position.x - 515);
			if (ascii_height > image_height)
				ascii_height = image_height;
			if (ascii_height < 1)
				ascii_height = 1;
		}
	}
		
	if (button2_pressed)
	{
		//184
		scroll_image_width->position.x = cursor_pos.x;
		if (scroll_image_width->position.x < 96)
			scroll_image_width->position.x = 96;
		else if (scroll_image_width->position.x > 280)
			scroll_image_width->position.x = 280;
		if (picture != nullptr)
		{
			ascii_width = static_cast<float>(image_width) / 184.0f * static_cast<float>(scroll_image_width->position.x - 95);
			if (ascii_width > image_width)
				ascii_width = image_width;
			if (ascii_width < 1)
				ascii_width = 1;
		}
	}
	
}
void AsciiWindow::DragAndDropImage(HDROP drop)
{
	char name[MAX_PATH];
	memset(name, 0, 254);
	LPSTR l = (LPSTR)&name;
	DragQueryFileA(drop, 0, l, 254);
	DragFinish(drop);
	Sprite *test = new Sprite(167, 15, 0);

	if (test->InitSprite(GraphicsDevice->device, name, 470, 430))
	{
		const size_t cSize = strlen(name) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, name, cSize);
		Gdiplus::Bitmap bm(wc);
		delete wc;
		
		strcpy(FileName, name);

		image_width = bm.GetWidth();
		image_height = bm.GetHeight();
		ascii_width = image_width;
		ascii_height = image_height;
		picture = test;
	}
}
void AsciiWindow::ManualSizeChange(POINT cursor_pos, RAWINPUT* input)
{
	if (picture != nullptr)
	{
		if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 530 && cursor_pos.y>518 && cursor_pos.x > 208 && cursor_pos.x < 230)
		{
			ascii_width += 1;
			if (ascii_width > image_width)
				ascii_width = image_width;
			scroll_image_width->position.x = 96.0f + 184.0f / static_cast<float>(image_width) * static_cast<float>(ascii_width);
		}
		else if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 542 && cursor_pos.y>530 && cursor_pos.x > 208 && cursor_pos.x < 230)
		{
			ascii_width -= 1;
			if (ascii_width < 1)
				ascii_width = 1;
			scroll_image_width->position.x = 96.0f + 184.0f / static_cast<float>(image_width) * static_cast<float>(ascii_width);
		}
		else if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 530 && cursor_pos.y>518 && cursor_pos.x > 628 && cursor_pos.x < 646)
		{
			ascii_height += 1;
			if (ascii_height > image_height)
				ascii_height = image_height;
			scroll_image_height->position.x = 516.0f + 184.0f / static_cast<float>(image_height) * static_cast<float>(ascii_height);
		}
		else if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 542 && cursor_pos.y>530 && cursor_pos.x > 628 && cursor_pos.x < 646)
		{
			ascii_height -= 1;
			if (ascii_height < 1)
				ascii_height = 1;
			scroll_image_height->position.x = 516.0f + 184.0f / static_cast<float>(image_height) * static_cast<float>(ascii_height);
		}
	}
	if (GetInput(0, 0)->data.mouse.ulButtons == 1 && cursor_pos.y < 590 && cursor_pos.y>560 && cursor_pos.x > 677 && cursor_pos.x < 785)
		exit(0);
}
void AsciiWindow::ImagePath(POINT cursor_pos, RAWINPUT* input)
{
	if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 590 && cursor_pos.y>560 && cursor_pos.x > 280 && cursor_pos.x < 530)
	{
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFilter = "(*.jpg, *.png, *.bmp)\0*.jpg; *.png; *.bmp;\0Wszystkie pliki\0*.*\0";

		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFile = FileName;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		GetOpenFileNameA(&ofn);
		

		Sprite *test = new Sprite(167, 15, 0);

		if (test->InitSprite(GraphicsDevice->device, ofn.lpstrFile, 470, 430))
		{
			const size_t cSize = strlen(ofn.lpstrFile) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, ofn.lpstrFile, cSize);
			Gdiplus::Bitmap bm(wc);
			delete wc;

			strcpy(FileName, ofn.lpstrFile);

			image_width = bm.GetWidth();
			image_height = bm.GetHeight();
			picture = test;
			ascii_width = static_cast<float>(image_width) / 184.0f * static_cast<float>(scroll_image_width->position.x - 95);
			if (ascii_width > image_width)
				ascii_width = image_width;
			else if (ascii_width < 1)
				ascii_width = 1;
			ascii_height = static_cast<float>(image_height) / 184.0f * static_cast<float>(scroll_image_height->position.x - 515);
			if (ascii_height > image_height)
				ascii_height = image_height;
			else if (ascii_height < 1)
				ascii_height = 1;
			
		}
	}
}
void AsciiWindow::Convert(POINT cursor_pos, RAWINPUT* input)
{
	if (picture != nullptr)
	{
		if (input->data.mouse.ulButtons == 1 && cursor_pos.y < 590 && cursor_pos.y>560 && cursor_pos.x > 10 && cursor_pos.x < 110)
		{
			if (AsciiCharacters.size() < 1)
			{
				MessageBox(0, "You can't convert an image without any ascii characters", "Error", 0);
				return;
			}
			char x[MAX_PATH];
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = ".txt\0*.txt;\0\0";
			strcpy(x, FileName);
			for (int i = strlen(x) - 1; i > 0; i--)
			{
				if (x[i] == '.')
					x[i + 1] = 0;
			}
			char ext[] = "txt";
			strncat(x, ext, 3);

			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFile = x;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			if (GetSaveFileNameA(&ofn) )
			{
				const size_t cSize = strlen(FileName) + 1;
				wchar_t* wc = new wchar_t[cSize];
				mbstowcs(wc, FileName, cSize);
				Conversion(wc, ofn.lpstrFile);
				delete wc;
			}
		}
	}
}
void AsciiWindow::Conversion(WCHAR* image_path, std::string ascii_path)
{
	Gdiplus::GdiplusStartupInput gdiSI;
	ULONG_PTR ulong_ptr;
	Gdiplus::GdiplusStartup(&ulong_ptr, &gdiSI, 0);
	Gdiplus::Bitmap bm(image_path);
	std::fstream fvar;
	fvar.open(ascii_path.c_str(), std::ios::out);
	int res_x = image_width / ascii_width;
	int res_y = image_height / ascii_height;
	float brightness = 0;

	for (int y = 0; y < bm.GetHeight(); y+=res_y)
	{
		for (int x = 0; x < bm.GetWidth(); x+=res_x)
		{
			for (int y2 = 0; y2 < res_y; y2++)
			{
				for (int x2 = 0; x2 < res_x; x2++)
				{
					Gdiplus::Color color;
					bm.GetPixel(x, y, &color);

					int r = (int)color.GetR();
					int g = (int)color.GetG();
					int b = (int)color.GetB();

					int big = r;
					if (big < g)
						big = g;
					if (big < b)
						big = b;

					int sml = r;
					if (sml > g)
						sml = g;
					if (sml > b)
						sml = b;


					 brightness += 50.0f / 255.0f * static_cast<float>(big) + (50.0f / 255.0f  * static_cast<float>(sml));
				}
			}
			brightness /= res_x * res_y;
			fvar << AsciiCharacters[toupper(static_cast<float>(AsciiCharacters.size()) / 100.0f*brightness)];
			brightness = 0;
		}
		fvar << "\n";
	}
	fvar.close();
}
void AsciiWindow::ChangeCharacters(RAWINPUT* input)
{
	if (picture != nullptr)
	{
		if (input->data.keyboard.VKey == 8 && input->data.keyboard.Flags == 0 && AsciiCharacters.size() > 0)
			AsciiCharacters.erase(AsciiCharacters.size() - 1, 1);
		if (input->data.keyboard.VKey > 31 && input->data.keyboard.Flags == 0 && AsciiCharacters.size() < 15)
		{

			BYTE key_state[256];
			HKL KeyLayout;
			char thekey[256];

			GetKeyboardState(key_state);
			KeyLayout = GetKeyboardLayout(0);
			UINT uScanCode2 = MapVirtualKeyExA(input->data.keyboard.VKey, 2, KeyLayout);

			ZeroMemory(&thekey[0], 256);
			ToAsciiEx(input->data.keyboard.VKey, uScanCode2, key_state, (LPWORD)thekey, 0, KeyLayout);
			AsciiCharacters += thekey;
		}
	}
	
}