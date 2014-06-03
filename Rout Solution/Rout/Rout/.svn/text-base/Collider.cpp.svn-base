#include "Collider.h"


Collider::Collider(float rWidth, float rHeight, float rDepth, D3DXVECTOR3 rPos)
{
	bBox.width = rWidth;
	bBox.height = rHeight;
	bBox.depth = rDepth;
	bBox.pos = rPos;
	//calculate the diagnol to get the bounding  sphere radius
	float sideA, sideB;
	//Get the two larges sides
	if( rWidth > rHeight || rWidth > rDepth)
	{
		sideA = rWidth;
		if(rHeight > rDepth)
		{
			sideB = rHeight;
		}
		else
		{
			sideB = rDepth;
		}
	}
	else
	{
		sideA = rHeight;
		sideB = rDepth;
	}
	//Compute Hypotenuse
	radius = sqrt(sideA*sideA + sideB*sideB);

}


Collider::~Collider(void)
{
}

bool Collider::Collides(Collider* eCollider)
{
	//if(abs(getDistance(eCollider->bBox.pos)) < abs(eCollider->radius + radius))
	{
		if ((bBox.pos.x < eCollider->bBox.pos.x + eCollider->bBox.width &&
			bBox.pos.x > eCollider->bBox.pos.x) ||
			(bBox.pos.x + bBox.width < eCollider->bBox.pos.x + eCollider->bBox.width &&
			bBox.pos.x + bBox.width > eCollider->bBox.pos.x))
		{
			if ((bBox.pos.z < eCollider->bBox.pos.z + eCollider->bBox.depth &&
			bBox.pos.z > eCollider->bBox.pos.z) || 
			(bBox.pos.z + bBox.depth < eCollider->bBox.pos.z + eCollider->bBox.depth &&
			bBox.pos.z + bBox.depth > eCollider->bBox.pos.z))
			{
				cout << " true";
				return true;
			}
		}

		/*if (bBox.pos.y > eCollider->bBox.pos.y + eCollider->bBox.height ||
			eCollider->bBox.pos.y > bBox.pos.y + bBox.height)
		{
			return false;
		}*/

		
		cout << "false in";
		return false;
	}
	cout << "false out";
	return false;

}

float Collider::getDistance(D3DXVECTOR3 ePos)
{
	float dX = ePos.x - bBox.pos.x;
	float dY = ePos.y - bBox.pos.y;
	float dZ = ePos.z - bBox.pos.z;
	return sqrt(dX*dX + dY*dY + dZ*dZ);
}