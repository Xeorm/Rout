#include "Key.h"


Key::Key(D3DXVECTOR3 pos, int iD)
{
	type = "Key";
	id = iD;
	ge3D_position = pos;
	ge3D_position.y -= 3;
	D3DXMatrixTranslation(&world,ge3D_position.x,ge3D_position.y,ge3D_position.z);
	collider = new Collider(6.0f, 6.0f, 6.0f, D3DXVECTOR3(ge3D_position.x - 4, ge3D_position.y - 4, ge3D_position.z - 4));
	found = false;
	color.a = 1;

}

void Key::init(ID3D10Device* device)
{
	md3dDevice = device;
	numModels = 1;
	vertexBufferArray = new ID3D10Buffer*[numModels];
	indexBufferArray = new ID3D10Buffer*[numModels];
	numVertices = new int[numModels];
	loadModel("..//..//..//Rout Assets//key.obj",0,.3f);
}

Key::~Key(void)
{
}
void Key::draw()
{
}
void Key::draw(ID3D10EffectPass* p, ID3D10EffectMatrixVariable* worldVar, ID3D10EffectMatrixVariable* WVPVar, D3DXMATRIX camMatrix)
{	
	if (!found)
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

int	Key::getID(void)
{
	return id;
}

void Key::interact()
{
	found = true;
}

Collider* Key::getCollider()
{
	return collider;
}

bool Key::Found()
{
	return found;
}