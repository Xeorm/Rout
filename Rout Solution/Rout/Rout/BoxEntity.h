#pragma once
#include "d3dUtil.h"
#include "Collider.h"
#include "Player.h"
#include "GameEntity3D.h"
class BoxEntity:
	public GameEntity3D
{
public:
	BoxEntity(void);
	BoxEntity(D3DXVECTOR3 pos, float width, float height, float depth);
	~BoxEntity(void);
	virtual void init(ID3D10Device* device);
	virtual void draw();
	Collider* getCollider(void);
	bool Visible;
private:
	Collider* collider;
};

