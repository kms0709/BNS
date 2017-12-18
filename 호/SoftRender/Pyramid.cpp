#include "stdafx.h"
#include "Pyramid.h"


Pyramid::Pyramid()
{
}


Pyramid::~Pyramid()
{
}

void Pyramid::Init( D3DXCOLOR c, D3DXMATRIXA16 & _world )
{
	worldMatrix = _world;

	D3DXVECTOR3 normal(0, 0, 0);
	vertexList.push_back(VertexPN(D3DXVECTOR3(0, 0, 0), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, -1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, -1), normal));

	vertexList.push_back(VertexPN(D3DXVECTOR3(0, 0, 0), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, 1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, -1), normal));

	vertexList.push_back(VertexPN(D3DXVECTOR3(0, 0, 0), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, 1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, 1), normal));

	vertexList.push_back(VertexPN(D3DXVECTOR3(0, 0, 0), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, -1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, 1), normal));

	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, -1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, 1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, -1), normal));

	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, -1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(1, -1, 1), normal));
	vertexList.push_back(VertexPN(D3DXVECTOR3(-1, -1, 1), normal));

	for (int i = 0; i < vertexList.size(); i += 3) {
		D3DXVECTOR3 v01 = vertexList[i + 1].p - vertexList[i + 0].p;
		D3DXVECTOR3 v02 = vertexList[i + 2].p - vertexList[i + 0].p;
		D3DXVec3Cross(&normal, &v01, &v02);

		vertexList[i].n = vertexList[i + 1].n = vertexList[i + 2].n = normal;
	}

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = material.Diffuse = material.Specular = c;

	D3DDevice->CreateVertexBuffer(vertexList.size() * sizeof(VertexPN), 0, VertexPN::FVF, D3DPOOL_MANAGED, &_pcBuffer, 0);

	VertexPN* pn;

	_pcBuffer->Lock(0, 0, (void**)&pn, 0);

	for (int i = 0; i < vertexList.size(); i++)
	{
		pn[i] = vertexList[i];
	}

	_pcBuffer->Unlock();


}

void Pyramid::Render()
{
	D3DDevice->SetMaterial(&material);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DDevice->SetStreamSource(0, _pcBuffer, 0, sizeof(VertexPN));

	D3DDevice->SetTransform( D3DTS_WORLD, &worldMatrix );
	D3DDevice->SetFVF( VertexPN::FVF );
	D3DDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		vertexList.size());
}
