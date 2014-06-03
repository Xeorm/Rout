#pragma once
#include <vector>
#include <string>
#include <list>
#include <math.h>
#include "enemy.h"
#include "Collider.h"
#include "Player.h"
#include "Node.h"
#include <time.h>

class Bonewheel :
	public Enemy
{
public:
	Bonewheel(void);
	Bonewheel(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating);
	~Bonewheel(void);

	void init(ID3D10Device* device);
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	void update(float t);
	void update();
	void interact(Player* player);

protected:
	float rotationSpeed;
	float wheelRotation; //radians
};

