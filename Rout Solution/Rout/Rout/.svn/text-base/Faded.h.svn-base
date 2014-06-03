#pragma once
#include "Enemy.h"
#include "Node.h"
#include <time.h>
#include "Particle.h"
class Faded: public Enemy
{
public:
	Faded(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating);
	~Faded(void);
	void init(ID3D10Device* device);
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	void update(float t);
	void update();
	void interact(Player* player);
	void drawParticles(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);

protected:
	Particle* particles;
};

