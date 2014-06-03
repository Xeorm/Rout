#pragma once
#include <D3DX10.h>	
#include "collisionentity.h"
class MovableEntity :
	public CollisionEntity
{
public:
	MovableEntity(void);
	~MovableEntity(void);
	virtual void draw() = 0;
	virtual void init(ID3D10Device* device) = 0;
	virtual void update() = 0;
private:
	
};

