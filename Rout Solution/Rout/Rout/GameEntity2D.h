#pragma once

#include <d3dx10.h>
#include <d3d10.h>
using namespace std;
/*
2D Game Entity
*/

static int RectWidth(RECT rect)
{
	return rect.right - rect.left;
}

static int RectHeight(RECT rect)
{
	return rect.bottom - rect.top;
}

class GameEntity2D
{
public:
	GameEntity2D(LPTSTR tex);
	GameEntity2D(void);
	~GameEntity2D(void);
	D3DX10_SPRITE sprite;
	//upper left corner is the point of registration
	int screenX;
	int screenY;
	int sizeX; //pixel resolution of the intended draw size
	int sizeY;
	RECT screenRect;
	LPTSTR textureLoc;
	void initSprite();
	//virtual void PreDraw(int winWidth, int winHeight);
	D3DXCOLOR color;
	D3DX10_IMAGE_LOAD_INFO LoadImageInfo;
	ID3D10ShaderResourceView *shaderResource;
	bool loaded;
};

