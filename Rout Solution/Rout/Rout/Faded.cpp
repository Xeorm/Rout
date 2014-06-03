#include "Faded.h"
#include "EntityManager.h"
#include "Particle.h"

Faded::Faded(D3DXVECTOR3 pos, int iD, int* path, int length, bool eating)
{
	type = "Faded";
	ge3D_position=pos;
	nodeID = iD;
	nodePath = path;
	nodeLength = length;
	currentNode = 0;
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	collider = new Collider(4.0f, 4.0f, 4.0f, D3DXVECTOR3(pos.x - 2, pos.y - 2, pos.z - 2));
	isEating = eating;
	lastNodeTime = 0;
	nodeWait = 0;
	particles = new Particle[20];
	fieldOfView = 4 ;
	for (int i = 0; i < 20; i++)
	{
		particles[i] = Particle("Faded",ge3D_position);
	}
}



void Faded::update(float t)
{
	float velocity = .005f;
	if(getDistance(EntityManager::getInstance()->currentPlayer->getPos()) <= 8.0f * fieldOfView)
	{
		isHunting = true;
	}
	else
	{
		isHunting = false;
	}
	if(isHunting)
	{
			if(ge3D_position.x < EntityManager::getInstance()->currentPlayer->getPos().x)
			{
				ge3D_position.x += velocity * t;
				collider->bBox.pos.x += velocity * t;

			}
			if(ge3D_position.x > EntityManager::getInstance()->currentPlayer->getPos().x)
			{
				ge3D_position.x -= velocity * t;
				collider->bBox.pos.x -= velocity * t;

			}
			if(ge3D_position.z > EntityManager::getInstance()->currentPlayer->getPos().z)
			{
				ge3D_position.z -= velocity * t;
				collider->bBox.pos.z -= velocity * t;

			}
			if(ge3D_position.z <EntityManager::getInstance()->currentPlayer->getPos().z)
			{
				ge3D_position.z += velocity * t;
				collider->bBox.pos.z += velocity * t;

			}
			for(int i =0; i < 20; i++)
			{
				particles[i].setPos(ge3D_position);
			}
	}
	//Normal Move Code
	else if(GetTickCount() - lastNodeTime > nodeWait)
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
			if(ge3D_position.x < nodes[nodePath[currentNode]]->getPos().x)
			{
				ge3D_position.x += velocity * t;
				collider->bBox.pos.x += velocity * t;

			}
			else if(ge3D_position.x > nodes[nodePath[currentNode]]->getPos().x)
			{
				ge3D_position.x -= velocity * t;
				collider->bBox.pos.x -= velocity * t;

			}
			else if(ge3D_position.z > nodes[nodePath[currentNode]]->getPos().z)
			{
				ge3D_position.z -= velocity * t;
				collider->bBox.pos.z -= velocity * t;

			}
			else if(ge3D_position.z < nodes[nodePath[currentNode]]->getPos().z)
			{
				ge3D_position.z += velocity * t;
				collider->bBox.pos.z += velocity * t;

			}
			for(int i =0; i < 20; i++)
			{
				particles[i].setPos(ge3D_position);
			}
		}
	}
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 look =	EntityManager::getInstance()->currentPlayer->getCamera()->position()-ge3D_position;
	look.y = 0.0f; // y-axis aligned, so project to xz-plane
	D3DXVec3Normalize(&look,&look);
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right,&up, &look);
	
	 world = D3DXMATRIX(right.x,right.y,right.z,0.0f,up.x,up.y,up.z,0.0f,look.x,look.y,look.z,0.0f,ge3D_position.x,ge3D_position.y,ge3D_position.z,1.0f);
	 for (int i =0;i<20;i++)
	 {
		 particles[i].update(t);
	 }
}

void Faded::update()
{

}

void Faded::interact(Player* player)
{
	if(player->IsAlive())
	{
		player->kill(false);
	}
}



void Faded::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{	
	for (DWORD i = 0; i<numModels;i++)
	{
	worldVar->SetMatrix((float*)&world);
	D3DXMATRIX temp = world * camMatrix;
	WVPVar->SetMatrix((float*)&temp);
	p->Apply(0);
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[i], &stride, &offset);
	md3dDevice->IASetIndexBuffer(indexBufferArray[i], DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(6, 0, 0);
	}
	
}

void Faded::drawParticles(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{
	for (int i =0; i<20; i++)
	{
		particles[i].draw(p,worldVar,WVPVar,camMatrix);
	}
}
void Faded::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	matrices = new D3DXMATRIX[numModels];

	//set up vertex buffer
	Vertex* vertices = new Vertex[4];
	vertices[0] = Vertex(-1.5f,-1.5f,0.0f,0.0f,0.0f,-1.0f,1.0f,1.0f);
	vertices[1] = Vertex(1.5f,-1.5f,0.0f,0.0f,0.0f,-1.0f,0.0f,1.0f);
	vertices[2] = Vertex(1.5f,1.5f,0.0f,0.0f,0.0f,-1.0f,0.0f,0.0f);
	vertices[3] = Vertex(-1.5f,1.5f,0.0f,0.0f,0.0f,-1.0f,1.0f,0.0f);

	D3D10_BUFFER_DESC vbd;
    vbd.Usage = D3D10_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * 4;
    vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA vinitData;


    vinitData.pSysMem = vertices;
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &vertexBufferArray[0]));
	//really silly index buffer
	DWORD* i = new DWORD[6];

	i[0]= 0;
	i[1]=1;
	i[2]=2;
	i[3]=0;
	i[4]=2;
	i[5]=3;

	D3D10_BUFFER_DESC ibd;
    ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * 6;
    ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = i;
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &indexBufferArray[0]));

	for (int i =0;i<20;i++)
	{
		particles[i].init(device);
	}
}

Faded::~Faded(void)
{
}

