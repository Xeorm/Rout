#pragma once
#include "d3dUtil.h"
#include <math.h>
#include <iostream>
using namespace std;
class Collider
{
public:
	Collider(float rWidth, float rHeight, float rDepth, D3DXVECTOR3 rPos);
	~Collider(void);

	bool Collides(Collider* eCollider);
	//CalcDistance
	float getDistance(D3DXVECTOR3 ePos);
	//CollisionBox
	
	//CollisionSphere
	float radius;
public:
	struct Rectangle
	{
		D3DXVECTOR3 pos;
		float width;
		float height;
		float depth;
	};
	Rectangle bBox;
};

