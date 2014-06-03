#include "GameEntity3D.h"


GameEntity3D::GameEntity3D(void)
{
}

GameEntity3D::GameEntity3D(string fileName)
{


}
GameEntity3D::GameEntity3D(D3DXVECTOR3 pos)
{
	ge3D_position = pos;
}

GameEntity3D::~GameEntity3D(void)
{
}

string GameEntity3D::getType(void)
{
	return type;
}

D3DXVECTOR3 GameEntity3D::getPos(void)
{
	return ge3D_position;
}

void GameEntity3D::setTexture(ID3D10ShaderResourceView* texture)
{
	//*shaderResource = texture;
}

void GameEntity3D::loadModel(string fileName,int model, float scale)
{
	vector<D3DXVECTOR3> vertexVector;
	vector<D3DXVECTOR3> normalVector;
	vector<D3DXVECTOR2> texVector;

	Vertex* faceVector;
	int count;
	ifstream file(fileName);
	string line;
	string temp;
	stringstream ss;
	stringstream parser;
	float x,y,z;
	int a,b,c;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file,line);
			ss.str(line);
			ss>>temp;
			if (temp.compare("v")==0)
			{
				ss>>x;
				ss>>y;
				ss>>z;
				vertexVector.push_back(D3DXVECTOR3(x,y,z) * scale);
			}
			else if (temp.compare("vt")==0)
			{
				ss>>x;
				ss>>y;
				texVector.push_back(D3DXVECTOR2(x,y));
			}
			else if (temp.compare("vn")==0)
			{
				ss>>x;
				ss>>y;
				ss>>z;
				normalVector.push_back(D3DXVECTOR3(x,y,z));
			}
			else if (temp.compare("f")==0)
			{//possible code here to reduce space at the cost of more time loading and complexity
				for (int i=0;i<3;i++)
				{
				getline(ss,temp,'/');
				parser<<temp;
				parser>>a;
				parser.clear();
				getline(ss,temp,'/');
				parser<<temp;
				parser>>b;
				parser.clear();
				getline(ss,temp,' ');
				parser<<temp;
				parser>>c;
				parser.clear();
				faceVector[count]=Vertex(vertexVector[a-1],normalVector[c-1],texVector[b-1]);
				count++;
				}
			}
			else if (temp.compare("x")==0)
			{
				ss>>a;
				faceVector = new Vertex[a*3];
				count=0;
				numVertices[model] = a*3;
			}
			ss.clear();
		}
	}

	if(type.compare("Door")==0 || type.compare("Key")==0)
	{
		for(int k = 0; k < numVertices[model]; k++)
		{
			switch (id)
			{
			case 1:
				faceVector[k].color.x = 0.5f;
				faceVector[k].color.y = 0.25f;
				faceVector[k].color.z = 1.0f;
			break;
			case 2:
				faceVector[k].color.x = 0.3f;
				faceVector[k].color.y = 1.0f;
				faceVector[k].color.z = 0.3f;
			break;
			case 3: 
				faceVector[k].color.x = 0.3f;
				faceVector[k].color.y = 0.3f;
				faceVector[k].color.z = 1.0f;
			break;
			default:
			break;
			}
		}
	}

	D3D10_BUFFER_DESC vbd;
    vbd.Usage = D3D10_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * numVertices[model];
    vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA vinitData;


    vinitData.pSysMem = faceVector;
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &vertexBufferArray[model]));
	//really silly index buffer
	DWORD* i = new DWORD[numVertices[model]];

	for (DWORD j=0;j<numVertices[model];j++)
	{
		i[j]=j;
	}

	D3D10_BUFFER_DESC ibd;
    ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * numVertices[model];
    ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = i;
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &indexBufferArray[model]));
}

float GameEntity3D::getDistance(D3DXVECTOR3 ePos)
{
	float dX = ePos.x - ge3D_position.x;
	float dZ = ePos.z - ge3D_position.z;
	return sqrt(dX*dX + dZ*dZ);
}