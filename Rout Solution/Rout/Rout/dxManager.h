/************************************************************************************
 *	DirectX 10 Manager Class
 *	----------------------------------------
 *	code by : bobby anguelov - banguelov@cs.up.ac.za
 *	downloaded from : takinginitiative.wordpress.org
 *
 *	code is free for use in whatever way you want, however if you work for a game
 *	development firm you are obliged to offer me a job :P (haha i wish)
 ************************************************************************************/

#ifndef DXMANAGER
#define DXMANAGER

#include <windows.h>
#include <d3d10.h>
#include <list>
#include <vector>
#include <d3dx10.h>
#include "GameEntity2D.h"
#include "GameEntity3D.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "Torch.h"
#include "Player.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Light.h"
#include "Vertex.h"
#include "Bonewheel.h"
#include "Door.h"
#include "Key.h"
using namespace std;

//create a basic vertex container
struct vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;

	vertex( D3DXVECTOR3 p, D3DXVECTOR4 c )
	{
		pos = p;
		color = c;
	}
};

class dxManager
{
	/*******************************************************************
	* Members
	********************************************************************/	
public:
	ID3D10ShaderResourceView *shaderResource;
	D3DX10_IMAGE_LOAD_INFO LoadImageInfo;
	//list of GameEntities

	list<GameEntity2D>			entity2DList;
	vector<GameEntity3D*>		entity3DList;
	ID3D10ShaderResourceView	*textureArr[10];
	ID3D10ShaderResourceView	*specMapArr[1];

	void lightTorches();
private:

	//window handle
	HWND*						hWnd;

	//device vars
	ID3D10Device*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	D3D10_VIEWPORT				viewPort;
	ID3D10RasterizerState*		pRS;
	D3DXCOLOR					pClearColor;
	
	//light variables
	Light						pLights[80];	 // Global light, then player torch, then 62 wall torches, 
	int							lightTypes [80]; // then 4 lights for the Fated, then 4 lights for exterior lights
	int							active[80];

	//stencil variables
	ID3D10Texture2D*			pDepthStencilBuffer;
	ID3D10DepthStencilView*		pDepthStencilView;

	//input layout and vertex buffer
	ID3D10Buffer*				pVertexBuffer;
	ID3D10InputLayout*			pVertexLayout;

	//effects and techniques
	ID3D10Effect*				pBasicEffect;
	ID3D10EffectTechnique*		pBasicTechnique;

	//3D effects and techniques
	ID3D10Effect* pFX;
	ID3D10EffectTechnique* pTech;

	//effect variable pointers
	ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	
	//projection and view matrices
	D3DXMATRIX                  viewMatrix;
	D3DXMATRIX                  projectionMatrix;

	//Camera
	Camera*						pCamera;

	//World Matrices
	D3DXMATRIX					pWorld;
	D3DXMATRIX					pWVP;
	//Temp Camera Shit
	
	//3D Shader Resources
	ID3D10ShaderResourceView*	pDiffuseMapRV;
	ID3D10ShaderResourceView*	pSpecMapRV;

	//FX variables
	ID3D10EffectMatrixVariable*			pfxWVPVar;
	ID3D10EffectMatrixVariable*			pfxWorldVar;
	ID3D10EffectVariable*				pfxEyePosVar;
	ID3D10EffectVariable*				pfxLightVar;
	ID3D10EffectScalarVariable*			pfxLightType;
	ID3D10EffectScalarVariable*			pfxActiveVar;
	ID3D10EffectScalarVariable*			pfxNumLightsVar;
	ID3D10EffectShaderResourceVariable* pfxDiffuseMapVar;
	ID3D10EffectShaderResourceVariable* pfxSpecMapVar;
	ID3D10EffectMatrixVariable*			pfxTexMtxVar;


	//2D Stuff
	LPD3DX10SPRITE sprite;
	LPD3DX10FONT font;
	LPD3DX10FONT hudFont;
	float currentImageWidth;
	float currentImageHeight;
	ID3D10BlendState* blend;
	GameEntity2D* crosshair;
	int backBufferHeight;
	int backBufferWidth;

	//image stuff
	D3DX10_IMAGE_INFO InfoFromFile;


	/*******************************************************************
	* Methods
	********************************************************************/	
public:

	//constructor and destructor
	dxManager();
	~dxManager();

	//initialize directx device
	bool initialize(HWND*);	

	//renderScene
	void renderScene();	

	//render3DScene
	void render3DScene(void);

	//loadTexture
	void loadTextures();

	//loadImage
	bool loadImage(LPTSTR lpFileName);

	//loadTextures
	void load3DTextures(void);

	//newGame
	void newGame(void);

	//getCamera
	Camera* getCamera(void);

	
	bool firstTorchLitFlag;

private:
	//buildFX
	void buildFX();

	//buildVertexLayouts
	void buildVertexLayouts();

	//fatal error handler
	bool fatalError(LPCWSTR msg); 

	//flicker torch
	void flickerTorch(Light* light, float held);

	void colorTorch(Light* light, float distToTorch, float distToPlayer);

};

#endif