#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{	
}


Cube::~Cube ()
{
	SAFE_RELEASE(vertexBuffer);
}

void Cube::Init(D3DXMATRIXA16& world)
{
	matWorld = world;
	D3DXMatrixScaling(&matWorld, 0.1f, 0.1f, 0.1f);


	vector<D3DXVECTOR3> initPCVerts;
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(-1.0f, -1.0f, -1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(-1.0f, 1.0f, -1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(1.0f, 1.0f, -1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(1.0f, -1.0f, -1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(-1.0f, -1.0f, 1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(-1.0f, 1.0f, 1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(1.0f, 1.0f, 1.0f)));
	initPCVerts.push_back(D3DXVECTOR3(D3DXVECTOR3(1.0f, -1.0f, 1.0f)));

	for (int i = 0; i < initPCVerts.size(); ++i)
	{
		D3DXVec3TransformCoord(&initPCVerts[i], &initPCVerts[i], &matWorld);
	}


	D3DXVECTOR3 normal;

	normal = D3DXVECTOR3(0, 0, -1);
	PNVerts.push_back(VertexPN(initPCVerts[0], normal));
	PNVerts.push_back(VertexPN(initPCVerts[1], normal));
	PNVerts.push_back(VertexPN(initPCVerts[2], normal));
	PNVerts.push_back(VertexPN(initPCVerts[0], normal));
	PNVerts.push_back(VertexPN(initPCVerts[2], normal));
	PNVerts.push_back(VertexPN(initPCVerts[3], normal));

	normal = D3DXVECTOR3(0, 0, 1);
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));
	PNVerts.push_back(VertexPN(initPCVerts[5], normal));
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[7], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));

	normal = D3DXVECTOR3(-1, 0, 0);
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[5], normal));
	PNVerts.push_back(VertexPN(initPCVerts[1], normal));
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[1], normal));
	PNVerts.push_back(VertexPN(initPCVerts[0], normal));

	normal = D3DXVECTOR3(1, 0, 0);
	PNVerts.push_back(VertexPN(initPCVerts[3], normal));
	PNVerts.push_back(VertexPN(initPCVerts[2], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));
	PNVerts.push_back(VertexPN(initPCVerts[3], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));
	PNVerts.push_back(VertexPN(initPCVerts[7], normal));

	normal = D3DXVECTOR3(0, 1, 0);
	PNVerts.push_back(VertexPN(initPCVerts[1], normal));
	PNVerts.push_back(VertexPN(initPCVerts[5], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));
	PNVerts.push_back(VertexPN(initPCVerts[1], normal));
	PNVerts.push_back(VertexPN(initPCVerts[6], normal));
	PNVerts.push_back(VertexPN(initPCVerts[2], normal));

	normal = D3DXVECTOR3(0, -1, 0);
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[0], normal));
	PNVerts.push_back(VertexPN(initPCVerts[3], normal));
	PNVerts.push_back(VertexPN(initPCVerts[4], normal));
	PNVerts.push_back(VertexPN(initPCVerts[3], normal));
	PNVerts.push_back(VertexPN(initPCVerts[7], normal));


	D3DDevice->CreateVertexBuffer(PNVerts.size() * sizeof(VertexPN), 0, VertexPN::FVF, D3DPOOL_MANAGED, &vertexBuffer, 0);


	VertexPN* ver;
	vertexBuffer->Lock(0, 0, (void**)&ver, 0);
	
	for (int i = 0; i < PNVerts.size(); i++)
	{
		ver[i] = PNVerts[i];
	}
	vertexBuffer->Unlock();

}



void Cube::cubeUpdate(D3DXMATRIXA16& world)
{
	matWorld = world;
}




void Cube::Render()
{
	D3DDevice->SetMaterial(&material);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexPN));
	D3DDevice->SetFVF(VertexPN::FVF);
	D3DDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		PNVerts.size());
}

void Cube::setmaterialColor(D3DXCOLOR c)
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = material.Diffuse = material.Specular = c;

}
