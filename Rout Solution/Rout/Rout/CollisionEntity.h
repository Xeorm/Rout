#pragma once
#include "GameEntity3D.h"

class CollisionEntity :
	public GameEntity3D
{

public:
	struct Rectangle
	{
		D3DXVECTOR3 pos;
		int width;
		int height;
		int depth;
	};
	Rectangle rect;
	CollisionEntity(void);
	CollisionEntity(string);
	virtual void draw();
	virtual void init(ID3D10Device* device);
	CollisionEntity(D3DXVECTOR3 pos, int width, int height, int depth);
	~CollisionEntity(void);
	/*
		Collides compares this CollisionEntity's AABB
		against another CollisionEntity's AABB and returns
		false if the two are not colliding
	*/
	bool collides(CollisionEntity* entity);
protected:
	
	string fileName;
};

