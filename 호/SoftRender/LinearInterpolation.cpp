#include "StdAfx.h"
#include "LinearInterpolation.h"
#include "Cube.h"
#include "Action.h"
#include "ActionMove.h"
#include "ActionSequence.h"
#include "ActionRepeat.h"

LinearInterpolation::LinearInterpolation( void )
	: cubeCtrl( nullptr )
{
}

LinearInterpolation::~LinearInterpolation( void )
{
	SAFE_RELEASE( cubeCtrl );
}

void LinearInterpolation::Init()
{
	cubeCtrl = new Cube;
	cubeCtrl->setmaterialColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
//	cubeCtrl->Init();
	


	ActionSequence* actionSeq = new ActionSequence;

	D3DXMATRIXA16 rotateMatrix;
	D3DXMatrixRotationY( &rotateMatrix, D3DX_PI / 3.0f );

	D3DCOLOR c = D3DCOLOR_XRGB( 255, 255, 0 );
	D3DXVECTOR3 p = D3DXVECTOR3( 10, 0, 0 );

	for ( int i = 0; i < 6; ++i )
	{
		ActionMove* actionMove = new ActionMove;

		lineVerts.push_back( VertexPC( p, c ) );
		actionMove->setStartPosition( p );

		D3DXVec3TransformCoord( &p, &p, &rotateMatrix );

		lineVerts.push_back( VertexPC( p, c ) );
		actionMove->setTargetPosition( p );

		actionMove->setActionTime( 1 );
		actionMove->AutoRelease();
		actionMove->setTargetObject( cubeCtrl );

		actionSeq->AddAction( actionMove );
	}

	ActionRepeat* actionRepeat = new ActionRepeat;
	actionSeq->setActionDelegate( actionRepeat );
	actionRepeat->SetAction( actionSeq );
	actionRepeat->AutoRelease();

	cubeCtrl->setAction( actionRepeat );
	actionRepeat->Start();
	actionSeq->AutoRelease();
}

void LinearInterpolation::Update()
{
	if ( cubeCtrl )
	{
		//cubeCtrl->Update();
	}
}

void LinearInterpolation::Render()
{
	D3DXMATRIXA16 identityMatrix;
	D3DXMatrixIdentity( &identityMatrix );

	D3DDevice->SetTexture( 0, nullptr );
	D3DDevice->SetTransform( D3DTS_WORLD, &identityMatrix );
	D3DDevice->SetFVF( VertexPC::FVF );
	D3DDevice->DrawPrimitiveUP( D3DPT_LINELIST,
		lineVerts.size() / 2,
		&lineVerts[0],
		sizeof( VertexPC ) );

	//if (cubeCtrl) cubeCtrl->Render();
}
