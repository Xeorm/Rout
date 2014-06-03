#pragma once

#include "MovableEntity.h"
#include "Player.h"
#include "Node.h"
#include "EmptyTile.h"
#include <string>
#include <vector>
using namespace std;
class Enemy :
	public MovableEntity
{
public:
	Enemy(void);
	~Enemy(void);
	void doAI();
	virtual void	init(ID3D10Device* device)=0;
	virtual void	draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix) = 0;
	void			draw();
	virtual void	update(float t) = 0;
	virtual void	interact(Player* player) = 0;
	void			setPostion(D3DXVECTOR3);
	Collider*		getCollider(void);
	void			addNode(Node* node);
	int			    getNodeID(void);
	void			getPlayerPath(EmptyTile* tile, int depth, int side);
protected:
	Collider*		collider;
	float			speed;
	int				nodeID;
	int*			nodePath;
	int				currentNode;
	int				currentHNode;
	int				nodeLength;
	int				nodeWait;
	bool			isEating;
	
	bool			isReturning;
	int				lastNodeTime;
	int				fieldOfView;
	vector<Node* >	nodes;
	//Hunting Nodes
	vector<EmptyTile* >	hNodes;
	D3DXMATRIX*	    matrices;
public:
	EmptyTile*		eTile;
	bool			isHunting;
};



