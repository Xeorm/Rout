#include "GameEntity2D.h"


GameEntity2D::GameEntity2D(LPTSTR tex)
{
	textureLoc = tex;
	loaded = false;
	color.a = 1.0f;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	screenX = 0;
	screenY = 0;
}

GameEntity2D::GameEntity2D(void)
{
	loaded = false;
}

GameEntity2D::~GameEntity2D(void)
{
}

void GameEntity2D::initSprite(void)
{
	sprite.TexCoord.x = 0.0f;
	sprite.TexCoord.y = 0.0f;
	sprite.TexSize.x = 1.0f;
	sprite.TexSize.y = 1.0f;

	sprite.ColorModulate = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	sprite.TextureIndex = 0;
}

/*
void GameEntity2D::PreDraw(int windowWidth, int windowHeight)
{
	screenRect.left = 0;
	screenRect.top = 0;
	screenRect.right = sizeX;//size.x;
	screenRect.bottom = sizeY;//size.y;
	OffsetRect(&screenRect, screenX, screenY);
	OffsetRect(&screenRect, RectWidth(screenRect) / 2, RectHeight(screenRect) / 2);

	float scaleX = (float)RectWidth(screenRect);
	float scaleY = (float)RectHeight(screenRect);

	D3DXVECTOR3 vPos ((float)screenRect.left, (float)screenRect.top, 10.0f);

	D3DXMATRIX scaleMatrix;
	D3DXMATRIX translationMatrix;

	D3DXMATRIX idMat;

	D3DXMatrixIdentity(&idMat);
		
	idMat._11 = 2.0f;
	idMat._22 = 2.0f;


	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, 1.0f);
	D3DXMatrixTranslation(&translationMatrix, vPos.x, vPos.y, vPos.z);

	sprite.matWorld = scaleMatrix * translationMatrix;
	D3DXMatrixScaling(&sprite.matWorld, 2.0f / windowWidth, 2.0f / windowHeight, 1.0f);
	
	D3DXMatrixIdentity(&sprite.matWorld);

	sprite.matWorld._11 *= 2.0f;
	sprite.matWorld._22 *= 2.0f;
	
	sprite.TexCoord.x = 0.0f;
	sprite.TexCoord.y = 0.0f;
	sprite.TexSize.x = 1.0f;
	sprite.TexSize.y = 1.0f;

	sprite.ColorModulate = color;
	sprite.pTexture = shaderResource;
	sprite.TextureIndex = 0;
}
*/