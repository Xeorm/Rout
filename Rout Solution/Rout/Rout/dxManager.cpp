#include "stdafx.h"
#include "dxManager.h"
#include <sstream>
#include "FullTile.h"
#include "EmptyTile.h"
#include "Particle.h"
/*******************************************************************
* Constructor
*******************************************************************/
dxManager::dxManager() :	pD3DDevice(NULL), pSwapChain(NULL), pRenderTargetView(NULL), pVertexBuffer(0),
							pVertexLayout(0), pBasicEffect(0), pRS(0), pDepthStencilView(0),
							pTech(0), pFX(0)

{
	D3DXMatrixIdentity(&pWorld);
	D3DXMatrixIdentity(&pWVP);
	pCamera = new Camera();
}
/*******************************************************************
* Destructor
*******************************************************************/
dxManager::~dxManager()
{
	if ( pRenderTargetView ) pRenderTargetView->Release();
	if ( pDepthStencilView ) pDepthStencilView->Release();
	if ( pDepthStencilBuffer ) pDepthStencilBuffer->Release();
	if ( pSwapChain ) pSwapChain->Release();
	if ( pD3DDevice ) pD3DDevice->Release();
	if ( pFX ) pFX->Release();
	if ( pVertexBuffer ) pVertexBuffer->Release();
	if ( pVertexLayout ) pVertexLayout->Release();
	for ( UINT i = 0; i < 1; i++)
	{
		if ( textureArr[i] ) textureArr[i]->Release();
		if ( specMapArr[i] ) specMapArr[i]->Release();
	}
}
/*******************************************************************
* Initializes Direct3D Device
*******************************************************************/
bool dxManager::initialize( HWND* hW )
{
	//window handle
	hWnd = hW;
	
	//get window dimensions
	RECT rc;
    GetClientRect( *hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

	//Set up DX swap chain
	//--------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
	//set buffer dimensions and format
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	
	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = *hWnd;
	swapChainDesc.Windowed = true;    
	
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	//Create the D3D device
	//--------------------------------------------------------------
	if ( FAILED( D3D10CreateDeviceAndSwapChain(		NULL, 
													D3D10_DRIVER_TYPE_HARDWARE, 
													NULL, 
													0, 
													D3D10_SDK_VERSION, 
													&swapChainDesc, 
													&pSwapChain, 
													&pD3DDevice ) ) ) return fatalError(L"D3D device creation failed");

	D3DX10CreateSprite(pD3DDevice, 0, &sprite);
	D3DX10CreateFontW( pD3DDevice, 40, 0, 0, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Impact", &font );
	D3DX10CreateFontW( pD3DDevice, 30, 0, 0, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Cambria", &hudFont );

	//SHADER STAGE
	//*****************************************************************************
		
	//Load Basic Effect and Technique 
	//--------------------------------------------------------------
	if ( FAILED( D3DX10CreateEffectFromFileW(	L"basicEffect.fx", 
												NULL, NULL, 
												"fx_4_0", 
												D3D10_SHADER_ENABLE_STRICTNESS, 
												0, 
												pD3DDevice, 
												NULL, 
												NULL, 
												&pBasicEffect, 
												NULL, 
												NULL	) ) ) return fatalError(L"Could not load effect file!");	

	pBasicTechnique = pBasicEffect->GetTechniqueByName("Render");
	
	//create matrix effect pointers
	pViewMatrixEffectVariable = pBasicEffect->GetVariableByName( "View" )->AsMatrix();
	pProjectionMatrixEffectVariable = pBasicEffect->GetVariableByName( "Projection" )->AsMatrix();
	pWorldMatrixEffectVariable = pBasicEffect->GetVariableByName( "World" )->AsMatrix();

	//INPUT ASSEMBLY STAGE
	//*****************************************************************************
	
	//Create Input Layout
	//--------------------------------------------------------------	
	
	D3D10_INPUT_ELEMENT_DESC layout[] = 
	{	
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = 2;

	D3D10_PASS_DESC PassDesc;
	pBasicTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
	if ( FAILED( pD3DDevice->CreateInputLayout( layout, 
												numElements, 
												PassDesc.pIAInputSignature,
												PassDesc.IAInputSignatureSize, 
												&pVertexLayout ) ) ) return fatalError(L"Could not create Input Layout!");

	// Set the input layout
	pD3DDevice->IASetInputLayout( pVertexLayout );

	//create vertex buffer (space for 100 vertices)
	//---------------------------------------------------------------------------------
	UINT numVertices = 400;

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( vertex ) * numVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	if ( FAILED( pD3DDevice->CreateBuffer( &bd, NULL, &pVertexBuffer ) ) ) return fatalError(L"Could not create vertex buffer!");;

	// Set vertex buffer
	UINT stride = sizeof( vertex );
	UINT offset = 0;
	pD3DDevice->IASetVertexBuffers( 0, 1, &pVertexBuffer, &stride, &offset );	

	//RASTERIZER STAGE SETUP
	//*****************************************************************************
	
	//Create viewport
	//--------------------------------------------------------------
	
	//create viewport structure	
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &viewPort);

	// OUTPUT-MERGER STAGE
	//*****************************************************************************

	//Create render target view
	//--------------------------------------------------------------
	
	//try to get the back buffer
	ID3D10Texture2D* pBackBuffer;
	if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) return fatalError(L"Could not get back buffer");

	//set back buffer dimensions
	D3D10_TEXTURE2D_DESC* bBufferDesc = new D3D10_TEXTURE2D_DESC();
	pBackBuffer->GetDesc(bBufferDesc);
	backBufferWidth = bBufferDesc->Width;
	backBufferHeight = bBufferDesc->Height;

	//try to create render target view
	if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) return fatalError(L"Could not create render target view");
	
	pBackBuffer->Release();
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// Set up the view and projection matrices
	//*****************************************************************************
	D3DXVECTOR3 camera[3] = {	D3DXVECTOR3(0.0f, 0.0f, -5.0f),
								D3DXVECTOR3(0.0f, 0.0f, 1.0f),
								D3DXVECTOR3(0.0f, 1.0f, 0.0f) };
	D3DXMatrixLookAtLH(&viewMatrix, &camera[0], &camera[1], &camera[2]);
		
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, (float)D3DX_PI * 0.5f, (float)width/(float)height, 0.1f, 100.0f);

	pClearColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	
	//set up blending
	D3D10_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D10_BLEND_DESC));
	desc.AlphaToCoverageEnable = TRUE;
	desc.BlendEnable[0] = TRUE;
	desc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	desc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	desc.BlendOp = D3D10_BLEND_OP_ADD;
	desc.SrcBlendAlpha = D3D10_BLEND_SRC_ALPHA;
	desc.DestBlendAlpha = D3D10_BLEND_INV_SRC_ALPHA;
	desc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	desc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	
	pD3DDevice->CreateBlendState(&desc, &blend);
	

	//everything completed successfully
	return true;
}


bool dxManager::loadImage(LPTSTR lpFileName)
{
	DWORD nDirecotryLength = 255;
	TCHAR lpCurrentDir[255];
	GetCurrentDirectory(nDirecotryLength,lpCurrentDir);
	//LPTSTR lpFileName = L"\\testA.bmp";
	lstrcat(lpCurrentDir,(LPCTSTR)lpFileName);
	if (FAILED(D3DX10GetImageInfoFromFile(lpCurrentDir, NULL, &InfoFromFile,NULL) ) )
	{
		return false;
	}

	LoadImageInfo.Width = InfoFromFile.Width;
	LoadImageInfo.Height = InfoFromFile.Height;
	LoadImageInfo.Depth = InfoFromFile.Depth;
	LoadImageInfo.FirstMipLevel = 1;
	LoadImageInfo.MipLevels = InfoFromFile.MipLevels;
	LoadImageInfo.Usage = D3D10_USAGE_DEFAULT;
	LoadImageInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	LoadImageInfo.CpuAccessFlags = 0;
	LoadImageInfo.MiscFlags = 0;
	LoadImageInfo.Format = InfoFromFile.Format;
	LoadImageInfo.Filter = D3DX10_FILTER_NONE;
	LoadImageInfo.MipFilter = D3DX10_FILTER_NONE;
	LoadImageInfo.pSrcInfo = &InfoFromFile;

	HRESULT result = D3DX10CreateShaderResourceViewFromFile(pD3DDevice, lpCurrentDir, &LoadImageInfo, NULL, &shaderResource,NULL);
	if( FAILED(result) ) {return false;}
	return true;
}


/*******************************************************************
* Scene Renderer
*******************************************************************/
void dxManager::renderScene()
{
	//clear scene
	pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0,0,0,0) );

	//create world matrix
	static float r;
	D3DXMATRIX w;
	D3DXMatrixIdentity(&w);

	//set effect matrices
	pWorldMatrixEffectVariable->SetMatrix(w);
	pViewMatrixEffectVariable->SetMatrix(viewMatrix);
	pProjectionMatrixEffectVariable->SetMatrix(projectionMatrix);


	sprite->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	//2D SPRITE DRAW CALLS
	list<GameEntity2D>::iterator it;
	for(it = entity2DList.begin(); it != entity2DList.end(); it++)
	{
		//it->PreDraw(backBufferWidth, backBufferHeight);
		sprite->DrawSpritesBuffered(&it->sprite, 1);
	}
	sprite->Flush();
	sprite->End();
	
	//draw text
	list<TextField*>::iterator ite;
	for (ite = EntityManager::getInstance()->textFieldList.begin();ite!=EntityManager::getInstance()->textFieldList.end();ite++)
	{
		if ((*ite)->changed) //get new bounding RECT
		{
			(*ite)->loc.bottom = (*ite)->loc.top + font->DrawTextA(NULL,(*ite)->getText().c_str(),-1,&((*ite)->loc),DT_CALCRECT,(*ite)->color);
			(*ite)->changed=false;
		}
		font->DrawTextA(NULL,(*ite)->getText().c_str(),-1,&((*ite)->loc),0,(*ite)->color);
	}
	
	
	// Set primitive topology 

	pD3DDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//get technique desc
	D3D10_TECHNIQUE_DESC techDesc;
	pBasicTechnique->GetDesc( &techDesc );
	

	//flip buffers
	pSwapChain->Present(0,0);
}

/*******************************************************************
* Scene 3D Renderer
*******************************************************************/
void dxManager::render3DScene(void)
{
	
	//Clears the screen with the given color and clears the stencil buffer
	pD3DDevice->ClearRenderTargetView(pRenderTargetView, pClearColor);
	pD3DDevice->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0);
	//Restores default states and sets Vertex Buffer
	pD3DDevice->OMSetDepthStencilState(0, 0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	pD3DDevice->OMSetBlendState(blend, blendFactors, 0xffffffff);
    pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3DDevice->IASetInputLayout(pVertexLayout);

	// Set fx file light and camera constants
	pfxEyePosVar->SetRawValue(&pCamera->position(), 0, sizeof(D3DXVECTOR3));
	pfxLightVar->SetRawValue(&pLights, 0, sizeof(Light) * 80);

	

	//pfxLightType->SetRawValue(lightTypes,0,sizeof(int)*72);
	//pfxActiveType->SetRawValue(active,0,sizeof(int)*72);
	
	// Set word view port matrix for this pass
	pWVP = pWorld * pCamera->view() * pCamera->proj();

	pfxWVPVar->SetMatrix((float*)&pWVP);
	pfxWorldVar->SetMatrix((float*)&pWorld);

	// Don't transform texture coordinates, so just use identity transformation.
	D3DXMATRIX texMtx;
	D3DXMatrixIdentity(&texMtx);
	pfxTexMtxVar->SetMatrix((float*)&texMtx);

	//Drawing logic
	if (!EntityManager::getInstance()->currentPlayer->IsAlive())
	{
		pLights[0].ambient.r += .01;
	}
	else
	{
		pLights[0].ambient.r = 0.005f;
	}
	pLights[1].pos = EntityManager::getInstance()->currentPlayer->getPos();
	
	pLights[68].pos = EntityManager::getInstance()->currentPlayer->playerPhylactery->getPos();
	
	//Set flickering for own torch
	flickerTorch(&pLights[1], 1.0f);




	//get color for own torch
	D3DXVECTOR3 torchPos;
	D3DXVECTOR3 resultVec;
	float leastDistance = 1000000;
	float playerDistance;
	torchPos = pLights[1].pos;
	for(int i = 0; i < EntityManager::getInstance()->fadedVector.size(); i++)
	{
		resultVec = torchPos - EntityManager::getInstance()->fadedVector[i]->getPos();
		if(resultVec.x * resultVec.x + resultVec.z * resultVec.z < leastDistance)
		{
			leastDistance = resultVec.x * resultVec.x + resultVec.z * resultVec.z;
		}
	}	
	colorTorch(&pLights[1], leastDistance, leastDistance);
	playerDistance = leastDistance;

	//have lights track Eaten
	for(int i = 62; i < 68; i++)
	{
		pLights[i].pos = EntityManager::getInstance()->eaterVector[i - 62]->getPos();
		pLights[i].pos.y += 2.0f;
	}


	//Set up our Technique description
	D3D10_TECHNIQUE_DESC techDesc;
    pTech->GetDesc( &techDesc );
	//temp


	//cull distant torches
	for (int j = 0; j < EntityManager::getInstance()->torchVector.size();j++)
	{
		if (EntityManager::getInstance()->torchVector[j]->lit == true)
		{
			//torchPos is currently the location of the player's light source
			resultVec = torchPos - EntityManager::getInstance()->torchVector[j]->getPos();
			//the visible diagonal of the maze is roughly 100 units
			//if you don't believe me, try changing the 10k downward
			if(resultVec.x * resultVec.x + resultVec.z * resultVec.z > 10000)
			{
				EntityManager::getInstance()->torchVector[j]->visible = false;
			}
			else
			{
				EntityManager::getInstance()->torchVector[j]->visible = true;
			}
		}
	}


	int numLights = 2;
	active[0]=0;
	active[1]=1;
	for (int x = 0; x < EntityManager::getInstance()->torchVector.size();x++)
	{
		if (EntityManager::getInstance()->torchVector[x]->lit == true && EntityManager::getInstance()->torchVector[x]->visible == true)
		{
			firstTorchLitFlag = true;
			active[numLights] = x+2;
			numLights++;
			flickerTorch(&pLights[x+2], 0.0f);
			torchPos = EntityManager::getInstance()->torchVector[x]->getPos();
			for(int i = 0; i < EntityManager::getInstance()->fadedVector.size(); i++)
			{
				resultVec = torchPos - EntityManager::getInstance()->fadedVector[i]->getPos();
				if(resultVec.x * resultVec.x + resultVec.z * resultVec.z < leastDistance)
				{
					leastDistance = resultVec.x * resultVec.x + resultVec.z * resultVec.z;
				}
			}
			colorTorch(&pLights[x+2], leastDistance, playerDistance);
			leastDistance = 1000000;
		}
	}
	
	for(int g = 55; g < 70; g++)
	{
		numLights++;
		active[numLights] = g;
	}

    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		pfxLightType->SetIntArray(lightTypes,0,72);
		pfxActiveVar->SetIntArray(active,0,numLights);
		pfxNumLightsVar->SetInt(numLights);
        pTech->GetPassByIndex( p )->Apply(0);

		

		//EmptyTile Draw Pass
		pfxDiffuseMapVar->SetResource(textureArr[0]);
		pfxSpecMapVar->SetResource(specMapArr[0]);
		D3DXMatrixIdentity(&texMtx);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		pTech->GetPassByIndex( p )->Apply(0);
		for each(FullTile* fullTile in EntityManager::getInstance()->fullTileVector)
		{
			fullTile->draw();
		}
	

		//FullTile DrawPass
		pfxDiffuseMapVar->SetResource(textureArr[0]);
		pfxSpecMapVar->SetResource(specMapArr[0]);
		D3DXMatrixIdentity(&texMtx);
		D3DXMatrixScaling(&texMtx, 32.0f, 32.0f, 32.0f);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		pTech->GetPassByIndex( p )->Apply(0);

		
		/*
		for each(EmptyTile* emptyTile in EntityManager::getInstance()->emptyTileVector)
		{
			emptyTile->draw();
		}*/
		
		EntityManager::getInstance()->boxVector[0]->draw();

		pfxDiffuseMapVar->SetResource(textureArr[1]);
		pfxSpecMapVar->SetResource(specMapArr[0]);
		D3DXMatrixIdentity(&texMtx);
		D3DXMatrixScaling(&texMtx, 32.0f, 32.0f, 32.0f);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		pTech->GetPassByIndex( p )->Apply(0);
		EntityManager::getInstance()->boxVector[1]->draw();

		//Torch Draw
		D3DXMatrixIdentity(&texMtx);
		pfxDiffuseMapVar->SetResource(textureArr[2]);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Torch* torch in EntityManager::getInstance()->torchVector)
		{
			torch->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}

		D3DXMatrixIdentity(&texMtx);
		pfxDiffuseMapVar->SetResource(textureArr[3]);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Bonewheel* bonewheel in EntityManager::getInstance()->bonewheelVector)
		{
			bonewheel->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}

		D3DXMatrixIdentity(&texMtx);
		pfxDiffuseMapVar->SetResource(textureArr[4]);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Eater* eater in EntityManager::getInstance()->eaterVector)
		{
			eater->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}

		//Faded
		D3DXMatrixIdentity(&texMtx);
		
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Faded* faded in EntityManager::getInstance()->fadedVector)
		{
			pfxDiffuseMapVar->SetResource(textureArr[5]);
			faded->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
			pfxDiffuseMapVar->SetResource(textureArr[6]);
			faded->drawParticles(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}
		//Doors
		D3DXMatrixIdentity(&texMtx);
		
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Door* door in EntityManager::getInstance()->doorVector)
		{
			pfxDiffuseMapVar->SetResource(textureArr[8]);
			door->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}

		//Keys
		D3DXMatrixIdentity(&texMtx);
		
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		for each(Key* key in EntityManager::getInstance()->keyVector)
		{
			pfxDiffuseMapVar->SetResource(textureArr[9]);
			key->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		}

		pfxDiffuseMapVar->SetResource(textureArr[1]);
		pfxSpecMapVar->SetResource(specMapArr[0]);
		D3DXMatrixIdentity(&texMtx);
		pfxTexMtxVar->SetMatrix((float*)&texMtx);
		pTech->GetPassByIndex( p )->Apply(0);
		EntityManager::getInstance()->currentPlayer->draw();

			pfxDiffuseMapVar->SetResource(textureArr[3]);
			pfxSpecMapVar->SetResource(specMapArr[0]);
			D3DXMatrixIdentity(&texMtx);
			pfxTexMtxVar->SetMatrix((float*)&texMtx);
			pTech->GetPassByIndex( p )->Apply(0);
			EntityManager::getInstance()->currentPhylactery->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		
		//draw player
			pfxDiffuseMapVar->SetResource(textureArr[7]);
			EntityManager::getInstance()->currentPlayer->draw(pTech->GetPassByIndex(p),pfxWorldVar,pfxWVPVar,pCamera->view()*pCamera->proj());
		
    }

	//2d sprite stuff
	sprite->Begin(D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK);
	sprite->DrawSpritesBuffered(&crosshair->sprite, 1);
	sprite->Flush();
	sprite->End();
	RECT rect;
	rect.top = 1.0f;
	rect.bottom = 1.0f;
	rect.left = 1.0f;
	rect.right = 800.0f;
	hudFont->DrawTextW(NULL, EntityManager::getInstance()->textTut.getText().c_str(),-1,&rect,DT_TOP | DT_NOCLIP | DT_WORDBREAK,D3DXCOLOR(1.0f,1.0f,1.0f,.5f));


	//flip buffers
	pSwapChain->Present(0,0);
}

void dxManager::flickerTorch(Light* light, float held)
{

	float variance = rand() % 20 - 10;
	variance /= 2000.0f;
	light->ambient.r += variance + held * variance;
	light->diffuse.r += variance + held * variance;
	light->specular.r += variance + held * variance;
	if(light->ambient.r > 0.8f + held * 0.2f)
	{
		light->ambient.r = 0.8f + held * 0.2f;
		light->diffuse.r = 0.8f + held * 0.2f;
		light->specular.r = 0.8f + held * 0.2f;

	}
	else if(light->ambient.r < 0.5f + held * 0.2f)
	{
		light->ambient.r = 0.5f + held * 0.2f;
		light->diffuse.r = 0.5f + held * 0.2f;
		light->specular.r = 0.5f + held * 0.2f;
	}
	
	//scale the other color components
	light->ambient.g = light->ambient.r * 5 / 8;
	light->diffuse.g = light->ambient.r * 5 / 8;
	light->specular.g = light->ambient.r * 5 / 8;
	light->ambient.b = light->ambient.r / 4;
	light->diffuse.b = light->ambient.r / 4;
	light->specular.b = light->ambient.r / 4;


	variance = rand() % 20 - 10;
	variance /= 2000.0f;
	light->att.x += variance + held * variance;
	if(light->att.x > 0.2f - held * 0.1f)
	{
		light->att.x = 0.2f - held * 0.1f;
	}
	else if(light->att.x < 0.1f - held * 0.05f)
	{
		light->att.x = 0.1f - held * 0.05f;
	}

	variance = rand() % 20 - 10;
	variance /= 2000.0f;
	light->att.y += variance + held * variance;
	if(light->att.y > 0.2f - held * 0.15f)
	{
		light->att.y = 0.2f - held * 0.15f;
	}
	else if(light->att.y < 0.015f - held * 0.0075f)
	{
		light->att.y = 0.015f - held * 0.0075f;
	}

	variance = rand() % 20 - 10;
	variance /= 10000.0f;
	light->att.z += variance + held * variance;
	if(light->att.z > 0.5f - held * 0.45f)
	{
		light->att.z = 0.5f - held * 0.45f;
	}
	else if(light->att.z < 0.125f - held * 0.105f)
	{
		light->att.z = 0.125f - held * 0.105f;
	}
}

void dxManager::colorTorch(Light* light, float distToTorch, float distToPlayer)
{
	//threshold distance is 32 * 32 (1024)
	float redComponent;
	float greenComponent;
	float brightness;
	brightness = light->ambient.r + light->ambient.g;

	//if beyond the threshold distance, the color ratio should be 8:5
	//if at the light, the color ratio should be 0:1
	redComponent = brightness * (8 - max(8 - distToTorch / (512 / (distToPlayer / 1536)) * 8, 0)) / 13;
	greenComponent = brightness - redComponent;

	light->ambient.r = light->diffuse.r = light->specular.r = redComponent;
	light->ambient.g = light->diffuse.g = light->specular.g = greenComponent; 
}

void dxManager::loadTextures()
{
	list<GameEntity2D>::iterator it;
	for(it = entity2DList.begin(); it != entity2DList.end(); it++)
	{
		if(!it->loaded)
		{
			if(loadImage(it->textureLoc))
			{
				it->shaderResource = shaderResource;
				it->sprite.pTexture = shaderResource;
				it->LoadImageInfo = LoadImageInfo;
				it->initSprite();
				it->loaded = true;
			}
		}
	}
}

/*******************************************************************
* Gets Camera
*******************************************************************/
Camera* dxManager::getCamera(void)
{
	return pCamera;
}

/*******************************************************************
* Builds FX Effect files
*******************************************************************/
void dxManager::buildFX()
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
  
	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	hr = D3DX10CreateEffectFromFileW(L"tex.fx", 0, 0, 
		"fx_4_0", shaderFlags, 0, pD3DDevice, 0, 0, &pFX, &compilationErrors, 0);
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
			ReleaseCOM(compilationErrors);
		}
		DXTraceW(__FILE__, (DWORD)__LINE__, hr, L"D3DX10CreateEffectFromFile", true);
	} 

	pTech = pFX->GetTechniqueByName("TexTech");
	
	pfxWVPVar        = pFX->GetVariableByName("gWVP")->AsMatrix();
	pfxWorldVar      = pFX->GetVariableByName("gWorld")->AsMatrix();
	pfxEyePosVar     = pFX->GetVariableByName("gEyePosW");
	pfxLightVar      = pFX->GetVariableByName("gLight");
	pfxLightType	 = pFX->GetVariableByName("gLightTypes")->AsScalar();
	pfxActiveVar     = pFX->GetVariableByName("gActive")->AsScalar();
	pfxNumLightsVar  = pFX->GetVariableByName("gNumLights")->AsScalar();
	pfxDiffuseMapVar = pFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	pfxSpecMapVar    = pFX->GetVariableByName("gSpecMap")->AsShaderResource();
	pfxTexMtxVar     = pFX->GetVariableByName("gTexMtx")->AsMatrix();
}


/*******************************************************************
* Builds Vertex Layouts
*******************************************************************/
void dxManager::buildVertexLayouts()
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0},
	};

	// Create the input layout
    D3D10_PASS_DESC PassDesc;
    pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
    HR(pD3DDevice->CreateInputLayout(vertexDesc, 4, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &pVertexLayout));
}

/*******************************************************************
* Load 3D Textures
*******************************************************************/
void dxManager::load3DTextures()
{
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"sandstone.dds", 0, 0, &textureArr[0], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"dirt.dds", 0, 0, &textureArr[1], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"defaultspec.dds", 0, 0, &specMapArr[0], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//TorchTex.png", 0, 0, &textureArr[2], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//BonewheelTex.png", 0, 0, &textureArr[3], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//EatenTex.png", 0, 0, &textureArr[4], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//Faded.png", 0, 0, &textureArr[5], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//FadedGas.png", 0, 0, &textureArr[6], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//player.png", 0, 0, &textureArr[7], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//Door.png", 0, 0, &textureArr[8], 0 ));
	HR(D3DX10CreateShaderResourceViewFromFileW(pD3DDevice, 
		L"..//..//..//Rout Assets//keytex.png", 0, 0, &textureArr[9], 0 ));
}

/*******************************************************************
* New Game
*******************************************************************/
void dxManager::newGame(void)
{
	// Resize the swap chain and recreate the render target view.
	D3D10_TEXTURE2D_DESC depthStencilDesc;
	
	depthStencilDesc.Width     = 800;
	depthStencilDesc.Height    = 600;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc.Usage          = D3D10_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	HR(pD3DDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer));
	HR(pD3DDevice->CreateDepthStencilView(pDepthStencilBuffer, 0, &pDepthStencilView));


	// Bind the render target view and depth/stencil view to the pipeline
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

	buildFX();
	buildVertexLayouts();

	LevelManager::getInstance()->LoadLevel("Maze.txt");
	EntityManager::getInstance()->initEntities(pD3DDevice);
	load3DTextures();

	//temp
	//BW.init(pD3DDevice);
	//Sets up the default lighting
	pLights[0].dir      = D3DXVECTOR3(0.57735f, -0.57735f, 0.57735f);
	pLights[0].ambient  = D3DXCOLOR(0.0015f, 0.0015f, 0.0015f, .5f);
	pLights[0].diffuse  = D3DXCOLOR(0.0015f, 0.0015f, 0.0015f, .5f);
	pLights[0].specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	lightTypes[0]=0;

	//should move it to the right shoulder, too, but that'll depend on camera's rotation, so one mo' while we get the rest of it working
	pLights[1].ambient = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
	pLights[1].diffuse = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
	pLights[1].specular = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
	pLights[1].att = D3DXVECTOR3(.5,.1,.01);
	
	//set up the light types for the array
	//light types for torches
	for(int i = 1; i < 69; i++)
	{
		lightTypes[i] = 1;
		pLights[i].ambient = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
		pLights[i].diffuse = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
		pLights[i].specular = D3DXCOLOR(0.5f, 0.2f, 0.0f, .5f);
		pLights[i].att = D3DXVECTOR3(.5,.1,.01);
	}
	//lights for doors
	for(int i = 55; i < 59; i++)
	{
		pLights[i].ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, .5f);
		pLights[i].diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, .5f);
		pLights[i].specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, .5f);
		pLights[i].att = D3DXVECTOR3(.5f,.1f,.3f);
	}
	//lights for keys
	for(int i = 59; i < 62; i++)
	{
		pLights[i].ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, .1f);
		pLights[i].diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, .1f);
		pLights[i].specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, .1f);
		pLights[i].att = D3DXVECTOR3(.99f,.95f,.9f);
	}
	//lights for eaten
	for(int i = 62; i < 68; i++)
	{
		pLights[i].ambient = D3DXCOLOR(0.9f, 0.2f, 0.2f, .7f);
		pLights[i].diffuse = D3DXCOLOR(0.9f, 0.2f, 0.2f, .7f);
		pLights[i].specular = D3DXCOLOR(0.9f, 0.2f, 0.2f, .7f);
		pLights[i].att = D3DXVECTOR3(.99f,.95f,.5f);
	}
	
	//light for phylactery
	pLights[68].ambient = D3DXCOLOR(0.2f, 0.2f, 0.9f, .7f);
	pLights[68].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.9f, .7f);
	pLights[68].specular = D3DXCOLOR(0.2f, 0.2f, 0.9f, .7f);
	pLights[68].att = D3DXVECTOR3(.1f,.1f,.1f);
	

	//initialize values for torches
	for(int i = 2; i < 55; i++)
	{

		////POSITIONS FOR TORCH LIGHTS HERE
		pLights[i].pos = EntityManager::getInstance()->torchVector[i-2]->getLightPos();
	}

	for(int i = 55; i < 59; i++)
	{
		pLights[i].pos = EntityManager::getInstance()->doorVector[i - 55]->getPos();
		pLights[i].pos.y += 4.0f;
	}
	for(int i = 59; i < 62; i++)
	{
		pLights[i].pos = EntityManager::getInstance()->keyVector[i - 59]->getPos();
	}

	for(int i = 62; i < 68; i++)
	{
		pLights[i].pos = EntityManager::getInstance()->eaterVector[i - 62]->getPos();
	}

	pLights[68].pos = EntityManager::getInstance()->currentPhylactery->getPos();

	pCamera->setLens(PI*0.25f, 800/600, 1.0f, 1000.0f);
	//pCamera->setPosition(EntityManager::getInstance()->currentPlayer->getPos());
	pCamera->setPosition(D3DXVECTOR3(EntityManager::getInstance()->currentPlayer->getPos().x - 4, EntityManager::getInstance()->currentPlayer->getPos().y + 8, EntityManager::getInstance()->currentPlayer->getPos().z));
	pCamera->mLook.z = 0;
	pCamera->mLook.x = -1;
	pCamera->mRight.z = 1;
	pCamera->mRight.x = 0;
	EntityManager::getInstance()->currentPlayer->setCamera(pCamera);
	EntityManager::getInstance()->currentPlayer->setPhylactery(EntityManager::getInstance()->currentPhylactery);

	//set up crosshairs
	crosshair = new GameEntity2D(L"\\..\\Assets\\Images\\CrossHairsPartial.png");
	if(loadImage(crosshair->textureLoc))
	{
		crosshair->shaderResource = shaderResource;
		crosshair->sprite.pTexture = shaderResource;
		crosshair->LoadImageInfo = LoadImageInfo;
		crosshair->initSprite();
		crosshair->loaded = true;
		D3DXMatrixIdentity(&crosshair->sprite.matWorld);
		crosshair->sprite.matWorld._11 *= .06f;
		crosshair->sprite.matWorld._22 *= .09f;
	}
	firstTorchLitFlag = false;
	
}

/*******************************************************************
* Fatal Error Handler
*******************************************************************/
bool dxManager::fatalError(LPCWSTR msg)
{
	MessageBox(*hWnd, msg, L"Fatal Error!", MB_ICONERROR);
	return false;
}

void dxManager::lightTorches()
{
	for each (Torch* torch in EntityManager::getInstance()->torchVector)
	{
		if (((EntityManager::getInstance()->currentPlayer->getPos().x - torch->getPos().x) * (EntityManager::getInstance()->currentPlayer->getPos().x - torch->getPos().x)
			+ (EntityManager::getInstance()->currentPlayer->getPos().z -torch->getPos().z) * (EntityManager::getInstance()->currentPlayer->getPos().z -torch->getPos().z)) < 24) //within 10 units
		{
			torch->lit= true;
		}
	}
}