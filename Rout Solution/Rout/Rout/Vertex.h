

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, 
		float nx, float ny, float nz, 
		float u, float v)
		: pos(x,y,z), normal(nx,ny,nz), texC(u,v){color.x = color.y = color.z = 1;}
	Vertex(D3DXVECTOR3 p,D3DXVECTOR3 n,D3DXVECTOR2 t):pos(p), normal(n),texC(t){color.x = color.y = color.z = 1;}
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 color;
	D3DXVECTOR2 texC;
};

#endif // VERTEX_H

