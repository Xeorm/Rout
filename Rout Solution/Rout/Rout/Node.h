#pragma once
#include "d3dUtil.h"
#include <vector>
class Node
{
public:
	Node(void);
	Node(D3DXVECTOR3 pos, int iD, int num, int timer);
	~Node(void);
	D3DXVECTOR3 getPos(void);
	int			getID(void);
	int			getNum(void);
	int			getTimer(void);
private:
	D3DXVECTOR3 position;
	int			nodeID;
	int			nodeNumber;
	int			nodeTimer;
};

