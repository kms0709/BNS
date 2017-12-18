#include "stdafx.h"
#include "GridCtrl.h"


GridCtrl::GridCtrl ()
{
}


GridCtrl::~GridCtrl ()
{
}

void GridCtrl::Init ()
{
	int lineCount = 1000;
	float interval = 0.1f;
	float max = lineCount * interval;
	D3DCOLOR color;

	//AxisXVector = D3DXVECTOR3 ( max, 0, 0 );
	//AxisZVector = D3DXVECTOR3 ( 0, 0, max );

	color = D3DCOLOR_XRGB( 255, 0, 0 );
	vertexList.push_back( VertexPC( D3DXVECTOR3( -max, 0.0f, 0.0f ), D3DCOLOR( color ) ) );
	vertexList.push_back( VertexPC( D3DXVECTOR3( max, 0.0f, 0.0f ), D3DCOLOR( color ) ) );

	color = D3DCOLOR_XRGB( 0, 255, 0 );
	vertexList.push_back( VertexPC( D3DXVECTOR3( 0.0f, -max, 0.0f ), D3DCOLOR( color ) ) );
	vertexList.push_back( VertexPC( D3DXVECTOR3( 0.0f, max, 0.0f ), D3DCOLOR( color ) ) );

	color = D3DCOLOR_XRGB( 0, 0, 255 );
	vertexList.push_back( VertexPC( D3DXVECTOR3( 0.0f, 0.0f, -max ), D3DCOLOR( color ) ) );
	vertexList.push_back( VertexPC( D3DXVECTOR3( 0.0f, 0.0f, max ), D3DCOLOR( color ) ) );

	for ( int i = 1; i <= lineCount; ++i ) {
		color = ( i % 5 == 0 ) ? D3DCOLOR_XRGB( 255, 255, 255 ) : D3DCOLOR_XRGB( 128, 128, 128 );
		vertexList.push_back( VertexPC( D3DXVECTOR3( -max, 0.0f, i ), D3DCOLOR( color ) ) );
		vertexList.push_back( VertexPC( D3DXVECTOR3( max, 0.0f, i ), D3DCOLOR( color ) ) );

		vertexList.push_back( VertexPC( D3DXVECTOR3( -max, 0.0f, -i ), D3DCOLOR( color ) ) );
		vertexList.push_back( VertexPC( D3DXVECTOR3( max, 0.0f, -i ), D3DCOLOR( color ) ) );

		vertexList.push_back( VertexPC( D3DXVECTOR3( i, 0.0f, -max ), D3DCOLOR( color ) ) );
		vertexList.push_back( VertexPC( D3DXVECTOR3( i, 0.0f, max ), D3DCOLOR( color ) ) );

		vertexList.push_back( VertexPC( D3DXVECTOR3( -i, 0.0f, -max ), D3DCOLOR( color ) ) );
		vertexList.push_back( VertexPC( D3DXVECTOR3( -i, 0.0f, max ), D3DCOLOR( color ) ) );
	}

	D3DXMATRIXA16 matS, matR, matWorld;
	D3DXMatrixScaling( &matS, 1.0f, 1.0f, 1.0f);

	Pyramid* pyramid = new Pyramid();

	D3DXMatrixRotationZ( &matWorld, D3DX_PI / 2.0f );
	matWorld = matS * matWorld;
	pyramid->Init( D3DCOLOR_XRGB( 255, 0, 0 ), matWorld );
	pyramidList.push_back( pyramid );

	pyramid = new Pyramid();
	D3DXMatrixRotationX( &matWorld, D3DX_PI );
	matWorld = matS * matWorld;
	pyramid->Init( D3DCOLOR_XRGB( 0, 255, 0 ), matWorld );
	pyramidList.push_back( pyramid );

	pyramid = new Pyramid();
	D3DXMatrixRotationX( &matWorld, -D3DX_PI / 2.0f );
	matWorld = matS * matWorld;
	pyramid->Init( D3DCOLOR_XRGB( 0, 0, 255 ), matWorld );
	pyramidList.push_back( pyramid );

	D3DDevice->CreateVertexBuffer(vertexList.size() * sizeof(VertexPC), 0, VertexPC::FVF, D3DPOOL_MANAGED, &_pcBuffer, 0);

	VertexPC* verpc;
	_pcBuffer->Lock(0, 0, (void**)&verpc, 0);

	for (int i = 0; i < vertexList.size(); i++)
	{
		verpc[i] = vertexList[i];
	}
	_pcBuffer->Unlock();

}

void GridCtrl::Render ()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity( &mat );

	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DDevice->SetTransform( D3DTS_WORLD, &mat );

	D3DDevice->SetStreamSource(0, _pcBuffer, 0, sizeof(VertexPC));
	D3DDevice->SetFVF( VertexPC::FVF );
	D3DDevice->DrawPrimitive(
		D3DPT_LINELIST,
		0,	vertexList.size());

	/*for each ( auto it in pyramidList ) {
		it->Render();
	}*/

	//for ( int i = 0; i < vertexList.size (); i += 2 ) {
	//	D3DXVECTOR3 v0 = vertexList[i];
	//	D3DXVECTOR3 v1 = vertexList[i + 1];
	//	
	//	v0 = v0.TransformCoord ( viewProjViewPort );
	//	v1 = v1.TransformCoord ( viewProjViewPort );

	//	MoveToEx ( hdc, v0.x, v0.y, NULL );
	//	LineTo ( hdc, v1.x, v1.y );

	//}

	//D3DXVECTOR3 v = AxisXVector.TransformCoord ( viewProjViewPort );
	//TextOut ( hdc, v.x, v.y, L"X", 1 );

	//v = AxisZVector.TransformCoord ( viewProjViewPort );
	//TextOut ( hdc, v.x, v.y, L"Z", 1 );

}
