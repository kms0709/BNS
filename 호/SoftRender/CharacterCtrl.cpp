#include "stdafx.h"
#include "CharacterCtrl.h"


CharacterCtrl::CharacterCtrl ()
	: positionVector ( 0, 0, 0 )
	, rotationY ( 0 )
	, speed ( 0.05f)
{

}


CharacterCtrl::~CharacterCtrl ()
{
}

void CharacterCtrl::Update (OBJMap* map)
{
	D3DXVECTOR3 tempPos = positionVector + positionVector;

	if ( GetKeyState ( 'A' ) & 0x8000 ) {
		rotationY -= 0.1f;
	}

	if ( GetKeyState ( 'D' ) & 0x8000 ) {
		rotationY += 0.1f;
	}



	D3DXVECTOR3 vDirection ( 0, 0, 1 );
	D3DXMATRIXA16 matRotationY;
	D3DXMatrixIdentity ( &matRotationY );

	D3DXMatrixRotationY ( &matRotationY, rotationY );
	D3DXVec3TransformNormal ( &vDirection, &vDirection, &matRotationY );

	if (GetKeyState('W') & 0x8000) {
		tempPos = tempPos + vDirection * speed;
	}

	if (GetKeyState('S') & 0x8000) {
		tempPos = tempPos - vDirection * speed;
	}



	if ((map->GetHeight(tempPos.x, tempPos.y, tempPos.z)))
	{
		positionVector = tempPos;
	}
	//else positionVector = tempPos;


	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation ( &translationMatrix, positionVector.x, positionVector.y, positionVector.z );
	worldMatrix =  matRotationY * translationMatrix;
}

D3DXVECTOR3 * CharacterCtrl::GetPosition ()
{
	return &positionVector;
}

D3DXMATRIXA16 * CharacterCtrl::GetWorldTM ()
{
	return &worldMatrix;
}

