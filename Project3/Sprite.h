#pragma once
#include<d3dx9.h>
#include <string>

class Sprite
{
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;

public:
	bool IsInitialized;
	D3DXVECTOR3 position;
	Sprite(float x = 0, float y = 0, float z = 0);
	~Sprite();

	bool InitSprite(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	virtual void Draw();
};
