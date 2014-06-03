#include "Phylactery.h"


Phylactery::Phylactery(void)
{
}

Phylactery::Phylactery(D3DXVECTOR3 pos)
{
	type = "Phylactery";
	ge3D_position = pos;
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	collider = new Collider(1.0f, 1.0f, 1.0f, D3DXVECTOR3(pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f));
}

Phylactery::~Phylactery(void)
{
}

Collider* Phylactery::getCollider(void)
{
	return collider;
}

void Phylactery::setPos(D3DXVECTOR3 pos)
{
	ge3D_position = pos;
	collider->bBox.pos = D3DXVECTOR3(pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f);
}

void Phylactery::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//phylactery.obj",0,0.125f);
}

void Phylactery::draw()
{

}

void Phylactery::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	worldVar->SetMatrix((float*)&world);
	D3DXMATRIX temp = world * camMatrix;
	WVPVar->SetMatrix((float*)&temp);
	
	p->Apply(0);
	for (DWORD i = 0; i<numModels;i++)
	{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[i], &stride, &offset);
	md3dDevice->IASetIndexBuffer(indexBufferArray[i], DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(numVertices[i]*3, 0, 0);
	}
}
