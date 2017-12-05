#include "stdafx.h"
#include "Group.h"


Group::Group()
	: materialTexture( nullptr )
{
}


Group::~Group()
{
	SAFE_RELEASE( materialTexture );
}

void Group::Render()
{
	D3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	D3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	D3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	D3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	D3DDevice->SetMaterial( &materialTexture->GetMaterial() );
	D3DDevice->SetTexture( 0, materialTexture->GetTexture() );
	D3DDevice->SetFVF( VertexPNT::FVF );
	D3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, vertexPNT.size() / 3, &vertexPNT[ 0 ], sizeof( VertexPNT ) );
}
