#pragma once
#include "d3dUtil.h"
#include "Collider.h"
#include "GameEntity3D.h"
class EmptyTile:
	public GameEntity3D
{
public:
	EmptyTile(void);
	EmptyTile(D3DXVECTOR3 pos);
	~EmptyTile(void);
	virtual void	init(ID3D10Device* device);
	virtual void	draw();
	Collider*		getCollider(void);
	void			addBTile(int side, EmptyTile* tile);
private:
	Collider*	collider;
	
public:
	//Bordering tiles Array

	//		   [1]
	//		[0][T][2]
	//		   [3]
	EmptyTile*	bTiles[4];
	bool		containsPlayer;
};

