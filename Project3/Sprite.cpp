#include "Sprite.h"

Sprite::Sprite(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	IsInitialized = false;
}
bool Sprite::InitSprite(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	if (!SUCCEEDED(D3DXCreateTextureFromFileExA(device, file.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texture)))
	{
		return false;
	}
	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		return false;
	}
	return true;
}
void Sprite::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, 0, 0, &position, color);
	sprite->End();
}
Sprite::~Sprite()
{
	if (texture)
	{
		texture->Release();
		texture = 0;
	}
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}

}

