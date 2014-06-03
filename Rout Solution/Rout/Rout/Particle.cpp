#include "Particle.h"
#include "EntityManager.h"
#include <random>
#include <time.h>
Particle::Particle()
{
}

Particle::Particle(string pType,D3DXVECTOR3 startPos)
{
	type=pType;

	ge3D_position=startPos;
	startPosition = startPos;
	active = true;
	if (type.compare("Faded") == 0)
	{
		timeLife = 3000;
		acceleration = D3DXVECTOR3(.0f,.00003f,.0f);
		velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
		scale = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	/*code here to adjust based on type.
	
	*/
}

void Particle::randomPosAdjust()
{	
	
	
	
	if (type.compare("Faded") == 0)
	{
		D3DXVECTOR3 playerVec =EntityManager::getInstance()->currentPlayer->getPos() -startPosition  ;
		D3DXVec3Normalize(&playerVec,&playerVec);
		float rando = (float)rand()/RAND_MAX;
		D3DXVECTOR3 randomVec(0.0f,-1.0f + rando * 2.0f,0.0f);
		D3DXVec3Cross(&randomVec,&playerVec,&randomVec);
		ge3D_position +=randomVec;
		rando = (float)rand()/RAND_MAX; 
		//ge3D_position.z += (-.5f + dist(eng) * 1.0f)* playerVec.z;
	}
}
void Particle::update(float timePassed)
{
	timePassed = 10;
	if (timePassed < timeLife)
	{
		timeLife -= timePassed;
		D3DXVECTOR3 playerVec =EntityManager::getInstance()->currentPlayer->getPos() -startPosition  ;
		D3DXVec3Normalize(&playerVec,&playerVec);
		velocity += acceleration * timePassed;
		ge3D_position.x += velocity.x * playerVec.x;
		ge3D_position.y += velocity.y * playerVec.y;
		ge3D_position.z += velocity.z * playerVec.z;
		scale.x -= .002f;
		scale.y -= .002f;
	}
	else
	{
	if (type.compare("Faded") == 0)
	{
		timeLife = 2000 + rand() % 4000;
		velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);
		float rando = (float)rand()/RAND_MAX;
		velocity.x += rando * .04f - .02f;
		rando = (float)rand()/RAND_MAX;
		velocity.z += rando *.04f -.02f;
		scale = D3DXVECTOR3(1.2f,1.2f,1.0f);
		ge3D_position=startPosition;
		
		randomPosAdjust();
	}
	}
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 look =	EntityManager::getInstance()->currentPlayer->getCamera()->position()-ge3D_position;
	look.y = 0.0f; // y-axis aligned, so project to xz-plane
	D3DXVec3Normalize(&look,&look);
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right,&up, &look);
	D3DXMATRIX scaling;
	D3DXMatrixScaling(&scaling,scale.x,scale.y,scale.z);
	 world = D3DXMATRIX(right.x,right.y,right.z,0.0f,up.x,up.y,up.z,0.0f,look.x,look.y,look.z,0.0f,ge3D_position.x,ge3D_position.y,ge3D_position.z,1.0f);
	 world = scaling * world;
}

bool Particle::isActive(void)
{
	return active;
}
void Particle::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	//matrices = new D3DXMATRIX[numModels];

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
    md3dDevice->CreateBuffer(&vbd, &vinitData, &vertexBufferArray[0]);
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
}
Particle::~Particle(void)
{
}

void Particle::draw()
{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(ge3D_mNumFaces*3, 0, 0);
}

void Particle::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{
	worldVar->SetMatrix((float*)&world);
	D3DXMATRIX temp = world * camMatrix;
	WVPVar->SetMatrix((float*)&temp);
	p->Apply(0);
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[0], &stride, &offset);
	md3dDevice->IASetIndexBuffer(indexBufferArray[0], DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(6, 0, 0);
}
void Particle::setPos(D3DXVECTOR3 pos)
{
	//ge3D_position= pos;
	startPosition = pos;
	
}