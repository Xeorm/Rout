#pragma once
#include "Collider.h"
#include "GameEntity3D.h"

class Torch :
	public GameEntity3D
{
public:
	Torch(void);
	Torch(D3DXVECTOR3 pos, int face);
	~Torch(void);
	void init(ID3D10Device* device);
	void draw();
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	Collider* getCollider(void);
	D3DXVECTOR3 getLightPos();
	bool lit;
	bool visible;
private:
	Collider* collider;
	int		  facing;
};

