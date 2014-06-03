#pragma once
#include "gameentity3d.h"
#include "Collider.h"
class Key :
	public GameEntity3D
{
public:
	Key(void);
	Key(D3DXVECTOR3 pos, int iD);
	~Key(void);
	void init(ID3D10Device* device);
	void draw();
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	int	 getID(void);
	void interact();
	Collider* getCollider();
	bool Found();
	D3DXCOLOR color;
private:
	Collider* collider;
	int		  keyID;
	bool found;
};

