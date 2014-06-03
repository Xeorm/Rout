#include "Node.h"


Node::Node(void)
{
}

Node::Node(D3DXVECTOR3 pos, int iD, int num, int timer)
{
	position = pos;
	nodeID = iD;
	nodeNumber = num;
	nodeTimer = timer;
}

Node::~Node(void)
{
}

D3DXVECTOR3 Node::getPos(void)
{
	return position;
}

int	Node::getID(void)
{
	return nodeID;
}

int Node::getNum(void)
{
	return nodeNumber;
}

int Node::getTimer(void)
{
	return nodeTimer;
}
