#include "Graphics.h"

Graphics::Graphics()
{

}
Graphics::~Graphics()
{
	if (device)
	{
		device->Release();
		device = 0;
	}
	if (direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}
void Graphics::InitGraphics(HWND hwnd, bool windowed)
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS present_parameter;
	ZeroMemory(&present_parameter, sizeof(present_parameter));
	present_parameter.Windowed = windowed;
	present_parameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_parameter.hDeviceWindow = hwnd;

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &present_parameter, &device)))
		MessageBox(0, "Error while initializating graphics", "ERROR", 0);
}
void Graphics::Clear(D3DCOLOR color)
{
	device->Clear(0, 0, D3DCLEAR_TARGET, color, 1.0f, 0);
}
void Graphics::Begin()
{
	device->BeginScene();
}
void Graphics::End()
{
	device->EndScene();
}
void Graphics::Present()
{
	device->Present(0, 0, 0, 0);
}