#include "StdAfx.h"
#include "GameObject.h"
#include "Action.h"

GameObject::GameObject( void )
	: direction( 0, 0, 0 )
	, position( 0, 0, 0 )
	, action( NULL )
	, rotaY(0)
	, prevPosition( 0, 0, 0 )
{
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixIdentity(&matS);
}


GameObject::~GameObject( void )
{
	SAFE_RELEASE( action );
}


void GameObject::Update()
{
	//if ( action ) action->Update();

	//D3DXVec3TransformCoord(&position, &position, &matS);


	D3DXMATRIXA16 matT, matR, rotationY;
	D3DXMatrixIdentity(&rotationY);

	D3DXMatrixRotationY(&rotationY, rotaY);

	D3DXMatrixTranslation( &matT, position.x, position.y, position.z );

	D3DXVECTOR3 d = position - prevPosition;
	if ( D3DXVec3LengthSq( &d ) > D3DX_16F_EPSILON )
	{
		direction = d;
	}

	/*D3DXMatrixLookAtLH( &matR,
		&D3DXVECTOR3( 0, 0, 0 ),
		&direction,
		&D3DXVECTOR3( 0, 1, 0 ) );*/
	//D3DXMatrixTranspose( &matR, &matR );

	worldMat = rotationY * matS * matT;

	prevPosition = position;
}

void GameObject::Render()
{

}
