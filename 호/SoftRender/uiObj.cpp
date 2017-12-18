#include "stdafx.h"
#include "uiObj.h"


uiObj::uiObj()
	: localPos( 0, 0, 0 )
	, parent( nullptr )
	, size( 0, 0 )
	, isDebugRender( false )
	, tag( 0 )
{
	D3DXMatrixIdentity( &worldMatrix );
}

uiObj::~uiObj()
{
	destroy();

}

void uiObj::update()
{
	updateWorldTM();
	updateChildren();

}

void uiObj::updateWorldTM()
{
	worldMatrix._41 = localPos.x;
	worldMatrix._42 = localPos.y;
	worldMatrix._43 = localPos.z;

	if ( parent ) {
		worldMatrix._41 += parent->worldMatrix._41;
		worldMatrix._42 += parent->worldMatrix._42;
		worldMatrix._43 += parent->worldMatrix._43;
	}
}

void uiObj::updateChildren()
{
	for each( auto it in childList ) {
		it->update();
	}
}

void uiObj::render( LPD3DXSPRITE sprite )
{
	if ( isDebugRender ) {
		float l = worldMatrix._41;
		float t = worldMatrix._42;
		float r = worldMatrix._41 + size.x;
		float b = worldMatrix._42 + size.y;

		D3DCOLOR c = D3DCOLOR_XRGB( 255, 0, 0 );
		std::vector<VertexRHWC> vecVertex;

		vecVertex.reserve( 8 );
		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( l, t, 0, 1 ), c ) );
		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( r, t, 0, 1 ), c ) );

		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( r, t, 0, 1 ), c ) );
		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( r, b, 0, 1 ), c ) );

		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( r, b, 0, 1 ), c ) );
		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( l, b, 0, 1 ), c ) );

		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( l, b, 0, 1 ), c ) );
		vecVertex.push_back( VertexRHWC( D3DXVECTOR4( l, t, 0, 1 ), c ) );

		D3DDevice->SetFVF( VertexRHWC::FVF );
		D3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, 4, &vecVertex[0], sizeof( VertexRHWC ) );
	}

	for each( auto it in childList ) {
		it->render( sprite );
	}

}

void uiObj::addChild(uiObj * child )
{
	child->parent = this;
	childList.push_back( child );
}


void uiObj::destroy()
{
	for each( auto it in childList ) {
		it->destroy();
	}
	//Release();
}

uiObj * uiObj::getChildByTag( int _tag )
{
	if ( tag == _tag )
		return this;

	for each( auto it in childList ) {
		uiObj* child = it->getChildByTag( _tag );
		if ( child != nullptr )
			return child;
	}
	return nullptr;

}



