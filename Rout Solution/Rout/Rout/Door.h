#pragma once
#include "GameEntity3D.h"
#include "Collider.h"
#include "Key.h"

class Door :
	public GameEntity3D
{
public:
	Door(void);
	Door(D3DXVECTOR3 pos, int iD, int face);
	~Door(void);
	void init(ID3D10Device* device);
	void draw(void);
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	int	 getID(void);
	void interact();
	Collider* getCollider();
	D3DXCOLOR color;
private:
	Collider* collider;
	int		  doorID;
	bool open;
	int		  faceing;
};

