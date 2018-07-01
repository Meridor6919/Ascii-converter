#pragma once
#include <d3d11.h>
#include <d3d9.h>
#include<D3DX10.h>
#include<D3DX11.h>

class Graphics
{
public:

	LPDIRECT3DDEVICE9 device;

	Graphics();
	~Graphics();
	void InitGraphics(HWND hwnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();
private:

	LPDIRECT3D9 direct3d;
};