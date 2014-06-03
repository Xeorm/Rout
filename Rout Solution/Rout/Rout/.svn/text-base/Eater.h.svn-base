#pragma once
#include "Enemy.h"
#include "Collider.h"
#include "Player.h"
#include "Node.h"
#include <string>
#include <time.h>
class Eater:
	public Enemy
{
public:
	Eater(void);
	Eater(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating);
	~Eater(void);
	void init(ID3D10Device* device);
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	void update(float t);
	void update();
	void interact(Player* player);
	void hunt(Player* player);
	void calcTile(void);
	void move(D3DXVECTOR3 pos, float t);
	void buildHPath(EmptyTile* tile, Player* player, int depth);
protected:
	//Collider* collider;
	D3DXVECTOR3*	scale;
	bool			isReturning;
	int				growingTime;
	float eatingTime;
};

