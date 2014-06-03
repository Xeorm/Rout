#pragma once
#include <string>
#include "d3dUtil.h"
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class GameEntity3D
{
public:
	GameEntity3D(void);
	GameEntity3D(string);
	GameEntity3D(D3DXVECTOR3 pos);
	~GameEntity3D(void);
	virtual void init(ID3D10Device* device) = 0;
	virtual void draw() = 0;
	
	string getType(void);
	D3DXVECTOR3 getPos(void);
	void setTexture(ID3D10ShaderResourceView* texture);
	float getDistance(D3DXVECTOR3 ePos);
	int id;
protected:

	void loadModel(string fileName,int model, float scale);
	string type;

	DWORD ge3D_mNumVertices;
	DWORD ge3D_mNumFaces;

	D3DXMATRIX world;
	D3DXVECTOR3 ge3D_position;
	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;//vertex Buffer
	ID3D10Buffer* mIB;//index Buffer

	ID3D10ShaderResourceView* shaderResource;
	
	int* numVertices;
	DWORD numModels;

	ID3D10Buffer** vertexBufferArray;//vertex Buffer
	ID3D10Buffer** indexBufferArray;//index Buffer
};

