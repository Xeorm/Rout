#include "Player.h"
#include "StateManager.h"
#include "AudioManager.h"

Player::Player(D3DXVECTOR3 pos)
{
	//Sets type
	type = "Player";
	
	//Sets Position Variables
	startPos = pos;
	spawnPos = pos;
	ge3D_position = pos;
	lastPos = pos;
	//Sets up state bools
	isAlive = false;
	hasPhylactery = true;
	collider = new Collider(2.5f, 2.5f, 2.5f, D3DXVECTOR3(pos.x - 1.25, pos.y + 3, pos.z - 1.25));
	speed = 4.5f;
	this->spawn(pos);
	hidden = true;
}

Camera* Player::getCamera()
{
	return playerCamera;
}
Collider* Player::getCollider(void)
{
	return collider;
}

Player::~Player(void)
{
	
}

bool Player::IsAlive(void)
{
	return isAlive;
}

void Player::setPhylactery(Phylactery* phyl)
{
	playerPhylactery = phyl;
	
}

void Player::setCamera(Camera* cam)
{
	playerCamera = cam;
	playerCamera->setPosition(ge3D_position);
	playerCamera->rebuildView();
}

void Player::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//Player.obj",0,5.0f);
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
}

void Player::update()
{
}
void Player::update(float t)
{
	if(hasPhylactery)
	{
		pLook   = playerCamera->mLook;
		pLook.y = 0;
		D3DXVECTOR3 phylPos;
		phylPos = ge3D_position + 3.0f * pLook;
		phylPos.y -= 2.0f;
		playerPhylactery->setPos(phylPos);
	}
	if (!isAlive)
	{
		deathTimer -= t;
	}
	if (deathTimer < 0)
	{
		isAlive = true;
		spawn(spawnPos);
		setPos(spawnPos);
		deathTimer = 1;
	}
}

void Player::kill(bool selfKill)
{
	if (!(hasPhylactery && selfKill))
	{
	isAlive = false;
	if(hasPhylactery  && !selfKill)
	{
		StateManager::getInstance()->changeState(Dead);
		AudioManager::getInstance()->StopBackground();
		//GameOver
	}
	else if(!hasPhylactery)
	{
		if(rand() % 2 == 0)
		{
			AudioManager::getInstance()->PlayDeathScream("DeathScream1.wav", D3DXVECTOR3(0, 0, 0));
		}
		else
		{
			AudioManager::getInstance()->PlayDeathScream("DeathScream2.wav", D3DXVECTOR3(0, 0, 0));
		}
		float distXFromSpawn;
		float distZFromSpawn;
		distXFromSpawn = spawnPos.x - getPos().x;
		distZFromSpawn = spawnPos.z - getPos().z;
		if(distXFromSpawn * distXFromSpawn + distZFromSpawn * distZFromSpawn < 16)
		{
			hasPhylactery = true;
		}
		else
		{
			//spawn(spawnPos);
			//setPos(spawnPos);
			//hasPhylactery = false;
			deathTimer = 500;
		}
	}
	else
	{
		deathTimer = 500;
		//spawn(getPos());
	}
	}
}

void Player::switchTop()
{
	if (!hidden)
	{
		lastPos = ge3D_position;
		pRight  = playerCamera->mRight;
		pLook   = playerCamera->mLook;
		pUp     = playerCamera->mUp;
		pLook.y = 0;
		D3DXVec3Normalize(&pLook, &pLook);
		world = D3DXMATRIX(pRight.x,pRight.y,pRight.z,0.0f,pUp.x,pUp.y,pUp.z,0.0f,pLook.x,pLook.y,pLook.z,0.0f,ge3D_position.x,ge3D_position.y,ge3D_position.z,1.0f);
	}
	hidden = !hidden;
}
void Player::bounce(D3DXVECTOR3 otherPos)
{
	float zOverlap;
	float xOverlap;
	xOverlap = getPos().x - otherPos.x;
	zOverlap = getPos().z - otherPos.z;
	if(abs(xOverlap) > abs(zOverlap))
	{
		if(getPos().x > otherPos.x)
		{
			setPos(D3DXVECTOR3(otherPos.x + 1.25f + 4.0f, getPos().y, getPos().z));
		}
		else
		{
			setPos(D3DXVECTOR3(otherPos.x - 1.25f - 4.0f, getPos().y, getPos().z));
		}
	}
	else
	{
		if(getPos().z > otherPos.z)
		{
			setPos(D3DXVECTOR3(getPos().x, getPos().y, otherPos.z + 1.25f + 4.0f));
		}
		else
		{
			setPos(D3DXVECTOR3(getPos().x, getPos().y, otherPos.z - 1.25f - 4.0f));
		}
	}
	
}

void Player::move(float x, float z, int millisElapsed)
{
	if(x != 0 || z != 0 && isAlive)
	{
		lastPos = ge3D_position;
		pRight  = playerCamera->mRight;
		pLook   = playerCamera->mLook;
		pUp     = playerCamera->mUp;
		pLook.y = 0;
		D3DXVec3Normalize(&pLook, &pLook);
		float secsElapsed = ((float)millisElapsed / 1000.0f);
		float dist = speed * secsElapsed;
		ge3D_position += D3DXVECTOR3(z*dist*pRight.x, 0.0f, z*dist*pRight.z);
		ge3D_position += D3DXVECTOR3(x*dist*pLook.x,  0.0f, x*dist*pLook.z);
		world = D3DXMATRIX(pRight.x,pRight.y,pRight.z,0.0f,pUp.x,pUp.y,pUp.z,0.0f,pLook.x,pLook.y,pLook.z,0.0f,ge3D_position.x,ge3D_position.y,ge3D_position.z,1.0f);
		collider->bBox.pos += D3DXVECTOR3(z*dist*pRight.x, 0.0f, z*dist*pRight.z);
		collider->bBox.pos += D3DXVECTOR3(x*dist*pLook.x,  0.0f, x*dist*pLook.z);
		if (hasPhylactery)
		{
					D3DXVECTOR3 phylPos;
		phylPos = ge3D_position + 3.0f * pLook;
		phylPos.y -= 2.0f;
		playerPhylactery->setPos(phylPos);
		}
		playerCamera->setPosition(ge3D_position);
		/*
		if(getDistance(pTile->getPos()) > 5.0f)
		{
			pTile->containsPlayer = false;
			if(getPos().x - pTile->getPos().x > 0)
			{
				pTile = pTile->bTiles[0];
			}
			else
			{
				pTile = pTile->bTiles[2];
			}
			if(getPos().z - pTile->getPos().z > 0)
			{
				pTile = pTile->bTiles[1];
			}
			else
			{
				pTile = pTile->bTiles[3];
			}
			pTile->containsPlayer = true;
			
		}*/
	}
}

void Player::setPos(D3DXVECTOR3 pos)
{
	ge3D_position = pos;
	collider->bBox.pos = D3DXVECTOR3(pos.x - 1.25, pos.y + 3, pos.z - 1.25);
	playerCamera->setPosition(pos);
}



void Player::placePhylactery()
{
	if(hasPhylactery)
	{
		hasPhylactery = false;
		playerPhylactery->setPos(D3DXVECTOR3(ge3D_position.x + playerCamera->mLook.x * 5, 1.0f, ge3D_position.z + playerCamera->mLook.z * 5));
		spawnPos = playerPhylactery->getPos();
		spawnPos.y = getPos().y;
	}
	else
		{
				float distXFromSpawn = spawnPos.x - getPos().x;
		float distZFromSpawn = spawnPos.z - getPos().z;
			if (distXFromSpawn * distXFromSpawn + distZFromSpawn * distZFromSpawn < 25)
			{
				hasPhylactery = true;
			}
	}

}

void Player::spawn(D3DXVECTOR3 pos)
{
	collider->bBox.pos = D3DXVECTOR3(pos.x - 1, pos.y + 3, pos.z - 1);
	ge3D_position = pos;
	lastPos = pos;
	hasPhylactery = true;
	isAlive = true;
}

void Player::draw()
{

}

bool Player::HasPhylactery(void)
{
	return hasPhylactery;
}

D3DXVECTOR3 Player::getLastPos(void)
{
	return lastPos;
}

void Player::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{	
	if (!hidden)
	{
	worldVar->SetMatrix((float*)&world);
	D3DXMATRIX temp = world * camMatrix;
	WVPVar->SetMatrix((float*)&temp);
	p->Apply(0);
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[0], &stride, &offset);
	md3dDevice->IASetIndexBuffer(indexBufferArray[0], DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(numVertices[0]*3, 0, 0);
	}
}
