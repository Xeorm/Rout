#include "CollisionEntity.h"


CollisionEntity::CollisionEntity(void)
{
}

void CollisionEntity::init(ID3D10Device* device)
{

}
CollisionEntity::CollisionEntity(string fileName):fileName(fileName)
{


}
CollisionEntity::CollisionEntity(D3DXVECTOR3 pos, int width, int height, int depth)
{
	ge3D_position = pos;
	rect.pos = D3DXVECTOR3(pos.x - width / 2, pos.y - height / 2, pos.z - depth / 2);
	rect.width = width;
	rect.height = height;
	rect.depth = depth;
}

CollisionEntity::~CollisionEntity(void)
{

}
void CollisionEntity::draw()
{
		UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(ge3D_mNumFaces*3, 0, 0);
}
bool CollisionEntity::collides(CollisionEntity* entity)
{
	if (rect.pos.x >= entity->rect.pos.x + entity->rect.width ||
		entity->rect.pos.x >= rect.pos.x + rect.width)
	{
		return false;
	}

	if (rect.pos.y >= entity->rect.pos.y + entity->rect.height ||
		entity->rect.pos.y >= rect.pos.y + rect.height)
	{
		return false;
	}

	if (rect.pos.z >= entity->rect.pos.z + entity->rect.depth ||
		entity->rect.pos.z >= rect.pos.z + rect.depth)
	{
		return false;
	}

	return true;
}