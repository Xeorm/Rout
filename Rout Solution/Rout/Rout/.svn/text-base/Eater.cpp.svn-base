#include "Eater.h"
#include <random>

Eater::Eater(void)
{
}

Eater::Eater(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating)
{
	type = "Eater";
	ge3D_position = pos;
	ge3D_position.y -= 3;
	nodeID = iD;
	nodePath = path;
	nodeLength = length;
	currentNode = 0;
	currentHNode = 0;
	fieldOfView = 3.0f;
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	collider = new Collider(4.0f, 4.0f, 4.0f, D3DXVECTOR3(ge3D_position.x - 2, ge3D_position.y - 2, ge3D_position.z - 2));
	isEating = true;
	if (isEating)
	{
		eatingTime = 10000;
	}
	isHunting = false;
	isReturning = false;
	nodeWait = 0;
}

Eater::~Eater(void)
{
}


void Eater::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 5;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//EatenCore.obj",0,.5f);
	loadModel("..//..//..//Rout Assets//EatenDarkLowLeft.obj",1,.5f);
	loadModel("..//..//..//Rout Assets//EatenDarkLowRight.obj",2,.5f);
	loadModel("..//..//..//Rout Assets//EatenTop.obj",3,.5f);
	loadModel("..//..//..//Rout Assets//EatenWideBack.obj",4,.5f);
	loadModel("..//..//..//Rout Assets//EatenWideFront.obj",5,.5f);
	matrices = new D3DXMATRIX[numModels];
	scale = new D3DXVECTOR3[numModels];
	for (int i = 0; i < numModels; i++)
	{
		scale[i] = D3DXVECTOR3(1,1,1);
		D3DXMatrixTranslation(&matrices[i],ge3D_position.x,ge3D_position.y,ge3D_position.z - 2.0f);
	}
	growingTime = 0;
}

void Eater::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{	

	for (DWORD i = 0; i<numModels;i++)
	{
		worldVar->SetMatrix((float*)&matrices[i]);
		D3DXMATRIX temp = matrices[i] * camMatrix;
		WVPVar->SetMatrix((float*)&temp);
		p->Apply(0);
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[i], &stride, &offset);
		md3dDevice->IASetIndexBuffer(indexBufferArray[i], DXGI_FORMAT_R32_UINT, 0);
		md3dDevice->DrawIndexed(numVertices[i]*3, 0, 0);
	}
}

D3DXVECTOR3 randomFloat()
{
	std::tr1::mt19937 eng;
	eng.seed(time(0));
	std::tr1::normal_distribution<float> dist;
	return D3DXVECTOR3(.0000001f+ dist(eng) *.00050f,.0000001f+ dist(eng) *.00000010f,.0000001f+ dist(eng) *.00050f);
}
void Eater::update(float t)
{
	growingTime += t/5.0f;
	if (!isEating)
	{
		//AI Code

		if(isHunting || isReturning)
		{
			if(getDistance(hNodes[currentHNode]->getPos()) < .50f)
			{
				ge3D_position.x = hNodes[currentHNode]->getPos().x;
				ge3D_position.z = hNodes[currentHNode]->getPos().z;
				collider->bBox.pos.x = hNodes[currentHNode]->getPos().x - 4;
				collider->bBox.pos.z = hNodes[currentHNode]->getPos().z - 4;
				eTile = hNodes[currentHNode];


				if(isHunting)
				{
					currentHNode++;
				}

				if(currentHNode == hNodes.size())
				{
					isHunting = false;
					currentHNode--;
					isReturning = true;
				}
				

				if(isReturning)
				{
					currentHNode--;
					hNodes.pop_back();
				}

				if(currentHNode == 0 && isReturning)
				{
					isReturning = false;
					hNodes.clear();
				}
			}
			else
			{
				move(hNodes[currentHNode]->getPos(), t);
			}
		}
		else
		{
			if(GetTickCount() - lastNodeTime > nodeWait)
			{
				nodeWait = nodes[nodePath[currentNode]]->getTimer();
				if(getDistance(nodes[nodePath[currentNode]]->getPos()) < .50f)
				{
					ge3D_position.x = nodes[nodePath[currentNode]]->getPos().x;
					ge3D_position.z = nodes[nodePath[currentNode]]->getPos().z;
					collider->bBox.pos.x = nodes[nodePath[currentNode]]->getPos().x - 4;
					collider->bBox.pos.z = nodes[nodePath[currentNode]]->getPos().z - 4;
					currentNode++;
		
					if(currentNode == nodeLength)
					{
						currentNode = 0;
					}
					lastNodeTime = GetTickCount();
				}
				else
				{
					move(nodes[nodePath[currentNode]]->getPos(), t);
				}
			}
		}
		calcTile();
	}	
	else
	{
		eatingTime -= t;
		if (eatingTime < 0)
		{
			isEating = false;
		}
	}

	if (growingTime > 500)
	{
		growingTime = false;
	}
	if (growingTime > 100)
	{
		scale[1] += randomFloat();
		scale[2] -= randomFloat();
		scale[0] -= randomFloat();
		scale[3] -= randomFloat();
		scale[4] += randomFloat();
		scale[5] += randomFloat();
	}
	else
	{
		scale[1] -= randomFloat();
		scale[2] += randomFloat();
		scale[0] += randomFloat();
		scale[3] += randomFloat();
		scale[4] -= randomFloat();
		scale[5] -= randomFloat();
	}
	if (growingTime > 200)
	{
		growingTime = 0;
	}
	for (int i = 0;i< numModels;i++)
	{
		if (scale[i].x < .3f)
		{
			scale[i].x=.3f;
		}
		else if (scale[i].x > 1.5f)
		{
			scale[i].x=1.5f;
		}
		if (scale[i].z < .3f)
		{
			scale[i].z=.3f;
		}
		else if (scale[i].z > 1.5f)
		{
			scale[i].z=1.5f;
		}
		if (scale[i].y > 1.2f)
		{
			scale[i].y = 1.2f;
		}
		else if (scale[i].y < .75f)
		{
			scale[i].y = .75f;
		}
		D3DXMATRIX scaling;
		D3DXMatrixScaling(&scaling,scale[i].x,scale[i].y,scale[i].z);
		D3DXMatrixTranslation(&matrices[i],ge3D_position.x ,ge3D_position.y ,ge3D_position.z - 2.0f );
		matrices[i] = scaling * matrices[i];
	}

}
void Eater::update()
{

}

void Eater::hunt(Player* player)
{
	float totalView = fieldOfView * 8.0f;
	float distance = getDistance(player->getPos());
	if(distance < totalView)
	{
		if(currentHNode != 0 && isHunting)
		{
			hNodes.resize(currentHNode + 1);
		}
		buildHPath(eTile, player, fieldOfView);
	}
	else if(isHunting)
	{
		isHunting = false;
		isReturning = true;
	}
}

void Eater::buildHPath(EmptyTile* tile, Player* player, int depth)
{
	hNodes.push_back(tile);
	if(depth > 0)
	{
		D3DXVECTOR3 sightLine = player->getPos() -  tile->getPos();
		if(tile->getDistance(player->getPos()) <= 4.0f)
		{
			isHunting = true;
		}
		else
		{
			if(sightLine.x >= 4 && tile->bTiles[3] != NULL)
			{
				buildHPath(tile->bTiles[3], player, depth - 1);
			}
			else if(sightLine.x <= -4 && tile->bTiles[1] != NULL)
			{
				buildHPath(tile->bTiles[1], player, depth - 1);
			}

			if(sightLine.z >= 4 && tile->bTiles[2] != NULL)
			{
				buildHPath(tile->bTiles[2], player, depth - 1);
			}
			else if(sightLine.z <= -4 && tile->bTiles[0] != NULL)
			{
				buildHPath(tile->bTiles[0], player, depth - 1);
			}

			if(!isHunting && hNodes.size() > 0)
			{
				hNodes.pop_back();
			}
		}
	}
}

void Eater::interact(Player* player)
{
	if(player->IsAlive())
	{
		player->kill(false);
	}
}

void Eater::move(D3DXVECTOR3 pos, float t)
{
	float velocity = .005f;
	if(ge3D_position.x < pos.x)
	{
		ge3D_position.x += velocity * t;
		collider->bBox.pos.x += velocity * t;
	}
	else if(ge3D_position.x > pos.x)
	{
		ge3D_position.x -= velocity * t;
		collider->bBox.pos.x -= velocity * t;
	}
	if(ge3D_position.z < pos.z)
	{
		ge3D_position.z += velocity * t;
		collider->bBox.pos.z += velocity * t;
	}
	else if(ge3D_position.z > pos.z)
	{
		ge3D_position.z -= velocity * t;
		collider->bBox.pos.z -= velocity * t;
	}
}

void Eater::calcTile(void)
{
	if(getDistance(eTile->getPos()) >= 4.0f)
	{
		//If the difference in X is positive
		if(eTile->getPos().x - getPos().x >= 4.0f && eTile->bTiles[3] != NULL)
		{	
			eTile = eTile->bTiles[3];
		}
		//If the difference in X is negative
		else if (eTile->getPos().x - getPos().x <= -4.0f && eTile->bTiles[1] != NULL)
		{
			eTile = eTile->bTiles[1];
		}	
		//If the difference in Z is positive
		else if(eTile->getPos().z - getPos().z >= 4.0f && eTile->bTiles[2] != NULL)
		{
			eTile = eTile->bTiles[2];
		}
		//If the difference in Z is negative
		else if(eTile->getPos().z - getPos().z <= -4.0f && eTile->bTiles[0] != NULL)
		{
			eTile = eTile->bTiles[0];
		}

	}
}