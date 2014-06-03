#pragma once
#include "d3dUtil.h"
#include "Collider.h"
#include "Player.h"
#include "GameEntity3D.h"
class FullTile:
	public GameEntity3D
{
public:
	FullTile(void);
	FullTile(D3DXVECTOR3 pos);
	~FullTile(void);
	virtual void init(ID3D10Device* device);
	virtual void draw();
	Collider* getCollider(void);
	void interact(Player* player);
private:
	Collider* collider;
};

