#pragma once
#include "gameentity3d.h"
#include <random>
class Particle: public GameEntity3D
{
public:
	Particle(string pType,D3DXVECTOR3 startPos);
	Particle();
	~Particle(void);
	void update(float timePassed);
	bool isActive(void);
	virtual void init(ID3D10Device* device);
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	virtual void draw();
	void setPos(D3DXVECTOR3 pos);
private:
	float timeLife;
	bool active;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 acceleration;
	D3DXVECTOR3 startPosition;
	void randomPosAdjust();
	D3DXVECTOR3 scale;
};

