#include "stdafx.h"
#include "Group.h"


Group::Group ()
	: materialTexture(nullptr)
{
}


Group::~Group ()
{
	SAFE_RELEASE ( materialTexture );
}

void Group::init()
{
	D3DDevice->CreateVertexBuffer(
		PNTVerts.size() * sizeof(VertexPNT),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0);

	VertexPNT* verPNT;
	vertexBuffer->Lock(0, 0, (void**)&verPNT, 0);

	for (int i = 0; i < PNTVerts.size(); i++)
	{
		verPNT[i] = PNTVerts[i];
	}
	vertexBuffer->Unlock();

}

void Group::Render()
{
	DWORD dwFillMode;
	D3DDevice->GetRenderState(D3DRS_FILLMODE, &dwFillMode);
	if ( dwFillMode == D3DFILL_WIREFRAME )
	{
		D3DDevice->SetTexture ( 0, NULL );
	}
	else
	{
		D3DDevice->SetTexture ( 0, materialTexture->GetTexture () );
	}



	D3DXMATRIXA16 mat;

	D3DXMatrixIdentity(&mat);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	D3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexPNT));


	D3DDevice->SetMaterial ( &materialTexture->GetMaterial() );
	D3DDevice->SetFVF ( VertexPNT::FVF );	

}
