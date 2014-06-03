#pragma once
#include "MovableEntity.h"
#include "Camera.h"
#include "Collider.h"
#include "Phylactery.h"
#include "EmptyTile.h"
class Player :
	public MovableEntity
{
public:
	Player(D3DXVECTOR3 pos);
	~Player(void);
	virtual void init(ID3D10Device* device);
	virtual void draw();
	void draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix);
	void update(); 
	void update(float t);
	void move(float x, float z, int millisElapsed);
	void kill(bool selfKill);
	void spawn(D3DXVECTOR3 pos);
	void setCamera(Camera* cam);
	Camera* getCamera();
	void setPhylactery(Phylactery* phyl);
	bool IsAlive(void);
	Collider* getCollider(void);
	D3DXVECTOR3 getLastPos(void);
	void setPos(D3DXVECTOR3 pos);	
	void placePhylactery();
	void bounce(D3DXVECTOR3 otherPos);
	void switchTop();
	bool HasPhylactery(void);	
	Phylactery* playerPhylactery;
private:
	//Position Variables
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 spawnPos;
	D3DXVECTOR3 lastPos;
	//Player Rotation
	D3DXVECTOR3 pRight;
	D3DXVECTOR3 pLook;
	D3DXVECTOR3 pUp;
	float deathTimer;
	Camera* playerCamera;
	bool hidden;
	bool isAlive;
	bool hasPhylactery;
	float speed;
	//Player collider
	Collider* collider;
public:
	EmptyTile* pTile;
};

