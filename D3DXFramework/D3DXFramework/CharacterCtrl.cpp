#include "stdafx.h"
#include "CharacterCtrl.h"


CharacterCtrl::CharacterCtrl()
	: position( 0, 0, 0 )
	, rotation( 0, 0, 0 )
{
	D3DXMatrixIdentity( &matWorld );
}


CharacterCtrl::~CharacterCtrl()
{
}

void CharacterCtrl::Init()
{


}

void CharacterCtrl::Release()
{
}

void CharacterCtrl::Update()
{
	//BYTE left;
	//if ( !MANAGER_INPUT->IsKey( SPKL_A, &left ) )
	//{
	//	if ( left == INPUT_PRESS_REPEAT )
	//		rotation.y -= 0.1f;
	//}

	//BYTE right;
	//if ( !MANAGER_INPUT->IsKey( SPKL_D, &right ) )
	//{
	//	if ( right == INPUT_PRESS_REPEAT )
	//		rotation.y += 0.1f;
	//}

	if ( !g_cursorActive )
		rotation.y = MANAGER_CAMERA->GetfRotY();

	D3DXMATRIXA16 matRotationY;
	D3DXVECTOR3 xDirection( 1.0f, 0.0f, 0.0f );
	D3DXVECTOR3 zDirection( 0.0f, 0.0f, 1.0f );
	D3DXMatrixRotationY( &matRotationY, rotation.y );
	D3DXVec3TransformNormal( &xDirection, &xDirection, &matRotationY );
	D3DXVec3TransformNormal( &zDirection, &zDirection, &matRotationY );

	BYTE left;
	if ( !MANAGER_INPUT->IsKey( SPKL_A, &left ) )
	{
		if ( left == INPUT_PRESS_REPEAT )
			position = position - xDirection;
	}

	BYTE right;
	if ( !MANAGER_INPUT->IsKey( SPKL_D, &right ) )
	{
		if ( right == INPUT_PRESS_REPEAT )
			position = position + xDirection;
	}

	BYTE forward;
	if ( !MANAGER_INPUT->IsKey( SPKL_W, &forward ) )
	{
		if ( forward == INPUT_PRESS_REPEAT )
			position = position + zDirection;
	}

	BYTE back;
	if ( !MANAGER_INPUT->IsKey( SPKL_S, &back ) )
	{
		if ( back == INPUT_PRESS_REPEAT )
			position = position - zDirection;
	}

	D3DXMATRIX pMat;
	D3DXMatrixTranslation( &pMat, position.x, position.y, position.z );

	MANAGER_CAMERA->SetTarget( position );

	matWorld = matRotationY * pMat;
}

void CharacterCtrl::Render()
{
}
