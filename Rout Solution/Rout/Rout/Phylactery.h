#pragma once
#include "GameEntity3D.h"
#include "Collider.h"

class Phylactery :
	public GameEntity3D
{
public:
	Phylactery(void);
	Phylactery(D3DXVECTOR3 pos);
	~Phylactery(void);
	void init(ID3D10Device* device);
	void draw();
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	Collider* getCollider(void);
	void setPos(D3DXVECTOR3 pos);
protected:
	Collider* collider;
	int nodeID;
	int facing;
};

