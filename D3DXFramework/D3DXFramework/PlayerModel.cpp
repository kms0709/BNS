#include "stdafx.h"
#include "PlayerModel.h"
#include "AllocateHierarchy.h"


PlayerModel::PlayerModel()
{
}


PlayerModel::~PlayerModel()
{
}

void PlayerModel::Init()
{
	popori_body = new SkinnedMesh( L"./data/test/popori", L"popori_body.X" );
	popori_body->SetPosition( D3DXVECTOR3( 0, 0, 0 ) );
	popori_body->SetRotation( D3DXVECTOR3( 0, -D3DX_PI / 2, 0 ) );

	popori_head = new SkinnedMesh( L"./data/test/popori", L"popori_head.X" );
	popori_tail = new SkinnedMesh( L"./data/test/popori", L"popori_tail.X" );
	weapon = new SkinnedMesh( L"./data/test/popori", L"weapon.X" );

//	headBone = D3DXFrameFind( popori_body->GetRoot(), "Bip01-Neck" );
//	headBone->pFrameSibling = popori_head->GetRoot();
	D3DXFrameFind( popori_body->GetRoot(), "Bip01-Neck" )->pFrameSibling = popori_head->GetRoot();
	
//	tailBone = D3DXFrameFind( popori_body->GetRoot(), "Skirt_Dummy" );
//	tailBone->pFrameSibling = popori_tail->GetRoot();
	D3DXFrameFind( popori_body->GetRoot(), "Skirt_Dummy" )->pFrameSibling = popori_tail->GetRoot();

//	handBone = D3DXFrameFind( popori_body->GetRoot(), "R_Sword" );
//	handBone->pFrameFirstChild = weapon->GetRoot();
	D3DXFrameFind( popori_body->GetRoot(), "R_Sword" )->pFrameFirstChild = weapon->GetRoot();

	n = 0;

	D3DXMatrixIdentity( &matWorld );
}

void PlayerModel::Release()
{
	D3DXFrameFind( popori_body->GetRoot(), "Bip01-Neck" )->pFrameSibling = NULL;
	D3DXFrameFind( popori_body->GetRoot(), "Skirt_Dummy" )->pFrameSibling = NULL;
	D3DXFrameFind( popori_body->GetRoot(), "R_Sword" )->pFrameFirstChild = NULL;

	SAFE_DELETE( weapon );
	SAFE_DELETE( popori_tail );
	SAFE_DELETE( popori_head );
	SAFE_DELETE( popori_body );
}

void PlayerModel::Update()
{

	if ( MANAGER_INPUT->IsKey( SPKL_LEFT ) )
	{
		if ( n > 0 ) --n;
		popori_body->SetAnimationIndex( n, true );
		popori_head->SetAnimationIndex( n, true );
		popori_tail->SetAnimationIndex( n, true );
	}

	if ( MANAGER_INPUT->IsKey( SPKL_RIGHT ) )
	{
		if ( n < 2 ) ++n;
		popori_body->SetAnimationIndex( n, true );
		popori_head->SetAnimationIndex( n, true );
		popori_tail->SetAnimationIndex( n, true );
	}

	popori_body->Update();
	popori_body->AnimationUpdate();
	popori_head->AnimationUpdate();
	popori_tail->AnimationUpdate();

}

void PlayerModel::Render()
{
	D3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	popori_body->SetMatWorld( matWorld );
	popori_body->Render();
}