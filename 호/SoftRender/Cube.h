#pragma once
#include "GameObject.h"

class D3DXVECTOR3;

class Cube : public GameObject
{
public:
	Cube ();
	virtual ~Cube ();

	void cubeUpdate(D3DXMATRIXA16& world);

	void Init(D3DXMATRIXA16& world);
	virtual void Render();

	virtual void setmaterialColor(D3DXCOLOR c);
	
private:
	vector<VertexPC>	vertexFormatList;
	vector<VertexPN>	PNVerts;
	D3DMATERIAL9		material;
	D3DXMATRIX			matWorld;
};

