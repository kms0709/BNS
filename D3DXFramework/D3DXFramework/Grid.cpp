#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::Init()
{
	int lineCount = 25;
	float interval = 1.0f;
	float max = lineCount * interval;

	lineList.push_back( LinePC( D3DXVECTOR3( -max, 0.0f, 0.0f ), D3DCOLOR_XRGB( 255, 0, 0 ) ) );
	lineList.push_back( LinePC( D3DXVECTOR3( max, 0.0f, 0.0f ), D3DCOLOR_XRGB( 255, 0, 0 ) ) );

	lineList.push_back( LinePC( D3DXVECTOR3( 0.0f, -max, 0.0f ), D3DCOLOR_XRGB( 0, 255, 0 ) ) );
	lineList.push_back( LinePC( D3DXVECTOR3( 0.0f, max, 0.0f ), D3DCOLOR_XRGB( 0, 255, 0 ) ) );

	lineList.push_back( LinePC( D3DXVECTOR3( 0.0f, 0.0f, -max ), D3DCOLOR_XRGB( 0, 0, 255 ) ) );
	lineList.push_back( LinePC( D3DXVECTOR3( 0.0f, 0.0f, max ), D3DCOLOR_XRGB( 0, 0, 255 ) ) );

	D3DCOLOR color;

	for ( int i = 1; i <= lineCount; ++i )
	{
		color = ( i % 5 == 0 ) ? D3DCOLOR_XRGB( 255, 255, 255 ) : D3DCOLOR_XRGB( 75, 75, 75 );

		lineList.push_back( LinePC( D3DXVECTOR3( -max, 0.0f, i * interval ), color ) );
		lineList.push_back( LinePC( D3DXVECTOR3( max, 0.0f, i * interval ), color ) );

		lineList.push_back( LinePC( D3DXVECTOR3( -max, 0.0f, -i * interval ), color ) );
		lineList.push_back( LinePC( D3DXVECTOR3( max, 0.0f, -i * interval ), color ) );

		lineList.push_back( LinePC( D3DXVECTOR3( i * interval, 0.0f, -max ), color ) );
		lineList.push_back( LinePC( D3DXVECTOR3( i * interval, 0.0f, max ), color ) );

		lineList.push_back( LinePC( D3DXVECTOR3( -i * interval, 0.0f, -max ), color ) );
		lineList.push_back( LinePC( D3DXVECTOR3( -i * interval, 0.0f, max ), color ) );
	}

	D3DXMatrixIdentity( &matrix );
}

void Grid::Release()
{
	lineList.clear();
	delete this;
}

void Grid::Update()
{
}

void Grid::Render()
{
	D3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	D3DDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
	D3DDevice->SetRenderState( D3DRS_NORMALIZENORMALS, FALSE );

	D3DDevice->SetTransform( D3DTS_WORLD, &matrix );
	D3DDevice->SetTexture( 0, 0 );

	D3DDevice->SetFVF( LinePC::FVF );
	LinePC tempLine[ 2 ];

	for ( int i = 0; i < lineList.size(); i += 2 )
	{
		tempLine[ 0 ] = lineList[ i ];
		tempLine[ 1 ] = lineList[ i + 1 ];

		D3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, &tempLine[ 0 ], sizeof( LinePC ) );
	}

}


