#include "Torch.h"


Torch::Torch(void)
{
}

Torch::Torch(D3DXVECTOR3 pos, int face)
{
	type = "Torch";
	ge3D_position = pos;
	collider = new Collider(1.0f, 1.0f, 1.0f, pos);
	D3DXMATRIX rotate;
	D3DXMatrixRotationY(&rotate, ((face-3) * 90.0f) / 57.29578f);

	facing = face;
	//ge3D_position = getLightPos();
		D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	world = rotate * world;
	visible = true;
}

Torch::~Torch(void)
{
}

Collider* Torch::getCollider(void)
{
	return collider;
}

void Torch::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//Torch.obj",0,.15f);
	
}

void Torch::draw()
{

}

void Torch::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{
	worldVar->SetMatrix((float*)&world);
	D3DXMATRIX temp = world * camMatrix;
	WVPVar->SetMatrix((float*)&temp);
	
	p->Apply(0);
	for (DWORD i = 0; i< numModels;i++)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		md3dDevice->IASetVertexBuffers(0, 1, &vertexBufferArray[i], &stride, &offset);
		md3dDevice->IASetIndexBuffer(indexBufferArray[i], DXGI_FORMAT_R32_UINT, 0);
		md3dDevice->DrawIndexed(numVertices[i]*3, 0, 0);
	}

}

D3DXVECTOR3 Torch::getLightPos()
{
	D3DXMATRIX rotate;
	D3DXMatrixRotationY(&rotate, ((facing-1) * 90.0f) / 57.29578f);
	D3DXVECTOR3 rotation(0.9f,.7f,0.0f);
	D3DXVec3TransformCoord(&rotation,&rotation,&rotate);
	return ge3D_position +rotation;
}