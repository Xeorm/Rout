#include "Bonewheel.h"


Bonewheel::Bonewheel(void)
{
}

Bonewheel::Bonewheel(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating)
{
	type = "BoneWheel";
	ge3D_position = pos;
	ge3D_position.y -= 0.25;
	nodeID = iD;
	nodePath = path;
	currentNode = 0;
	nodeLength = length;
	//D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	collider = new Collider(8.0f, 8.0f, 8.0f, D3DXVECTOR3(ge3D_position.x - 4, ge3D_position.y - 4, ge3D_position.z - 4));
	isEating = eating;
	nodeWait = 0;
}

Bonewheel::~Bonewheel(void)
{
}


void Bonewheel::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 3;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//BonewheelWheel.obj",0,.4f);
	loadModel("..//..//..//Rout Assets//BonewheelWheel.obj",1,.4f);
	loadModel("..//..//..//Rout Assets//BonewheelAxel.obj",2,.4f);
	matrices = new D3DXMATRIX[3];
	wheelRotation = 0;
	rotationSpeed = .02f;
}

void Bonewheel::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{

	for (int i = 0; i < numModels; i++)
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

void Bonewheel::update(float t)
{


	//AI Code
	
	float velocity = .05f;
	float rot=0;
	nodeWait=0;
	if(GetTickCount() - lastNodeTime > nodeWait)
	{
		nodeWait = nodes[nodePath[currentNode]]->getTimer();
		if(getDistance(nodes[nodePath[currentNode]]->getPos()) < .500f)
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
			if(ge3D_position.x < nodes[nodePath[currentNode]]->getPos().x)
			{
				ge3D_position.x += velocity * t;
				collider->bBox.pos.x += velocity * t;
				rot = 0;
				wheelRotation+=rotationSpeed * t;
			}
			else if(ge3D_position.x > nodes[nodePath[currentNode]]->getPos().x)
			{
				ge3D_position.x -= velocity * t;
				collider->bBox.pos.x -= velocity * t;
				wheelRotation+=rotationSpeed * t;
				rot = 2;
			}
			else if(ge3D_position.z > nodes[nodePath[currentNode]]->getPos().z)
			{
				ge3D_position.z -= velocity * t;
				collider->bBox.pos.z -= velocity * t;
				wheelRotation+=rotationSpeed * t;
				rot = 1;
			}
			else if(ge3D_position.z < nodes[nodePath[currentNode]]->getPos().z)
			{
				ge3D_position.z += velocity * t;
				collider->bBox.pos.z += velocity * t;
				rot = 3;
				wheelRotation+=rotationSpeed * t;			
			}
		}
	}
	if(getDistance(nodes[nodePath[currentNode]]->getPos()) < 5.00f)
	{
		rot -= (5 - getDistance(nodes[nodePath[currentNode]]->getPos())) / 5;
	}
	D3DXMATRIX wheelRotationMatrix;
	D3DXMATRIX wheelTranslate1;
	D3DXMATRIX wheelTranslate0;
	D3DXMatrixTranslation(&wheelTranslate0,0,0,3.0f);
	D3DXMatrixTranslation(&wheelTranslate1,0,0,-3.0f);
	D3DXMatrixRotationYawPitchRoll(&wheelRotationMatrix,(rot * 90.0f) / 57.29578f,0.0f,0.0f);
	D3DXMatrixTranslation(&matrices[2],ge3D_position.x,ge3D_position.y,ge3D_position.z);
	matrices[2] = wheelRotationMatrix * matrices[2];
	D3DXMatrixRotationYawPitchRoll(&wheelRotationMatrix,(rot * 90.0f) / 57.29578f,0.0f,-1 * wheelRotation);
	D3DXMatrixTranslation(&matrices[0],ge3D_position.x ,ge3D_position.y,ge3D_position.z);
	D3DXMatrixTranslation(&matrices[1],ge3D_position.x ,ge3D_position.y,ge3D_position.z);
	collider->bBox.pos.x = ge3D_position.x - 4;
	collider->bBox.pos.z = ge3D_position.z - 4;

	matrices[0] =  wheelTranslate0* wheelRotationMatrix *  matrices[0];
	matrices[1] = wheelTranslate1*wheelRotationMatrix *   matrices[1];
	
}

void Bonewheel::update()
{

}

void Bonewheel::interact(Player* player)
{
	if(player->IsAlive())
	{
		player->kill(false);
	}
}

