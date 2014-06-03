#include "Door.h"
#include "EntityManager.h"

Door::Door(D3DXVECTOR3 pos, int iD, int face)
{
	type = "Door";
	id = iD;
	faceing = face;
	ge3D_position = pos;
	ge3D_position.y -= 4;
	D3DXMATRIX rotate;
	D3DXMatrixRotationY(&rotate, ((face) * 90.0f) / 57.29578f);
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	world = rotate * world;
	collider = new Collider(8.0f, 8.0f, 8.0f, D3DXVECTOR3(ge3D_position.x - 4, ge3D_position.y - 4, ge3D_position.z - 4));
	open = false;
}

void Door::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//door.obj",0,1.2f);
}

Door::~Door(void)
{
}

void Door::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
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

int Door::getID(void)
{
	return doorID;
}

void Door::draw(void)
{

}

Collider* Door::getCollider()
{
	return collider;
}

void Door::interact()
{
	if (!open)
	{
		for each (Key* key in EntityManager::getInstance()->keyVector)
		{
			if (key->getID() == id && key->Found())
			{
				D3DXMATRIX translate;
				D3DXMatrixTranslation(&translate,3.0f,0.0f,0.0f);
				D3DXMATRIX rotate;
				D3DXMatrixRotationY(&rotate,90.0f * 4 / 57.29578f);

				switch (faceing)
				{
				case 0:
					D3DXMatrixTranslation(&world,ge3D_position.x + 3,ge3D_position.y,ge3D_position.z);
					break;
				case 1:
					D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z-3);
					break;
				}

				world = translate * rotate * world;
				open = true;
			}
		}
		EntityManager::getInstance()->currentPlayer->bounce(ge3D_position);
	}
}