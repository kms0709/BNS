#pragma once
#include "uiObj.h"

class uiImageView : public uiObj
{
public:
	uiImageView();
	virtual ~uiImageView();

	GETSET( D3DCOLOR, color, Color );
	//GETSET_ADD_REF( LPDIRECT3DTEXTURE9, texture, Texture );
	GETSET_REF( LPDIRECT3DTEXTURE9, texture, Texture );

	virtual void render( LPD3DXSPRITE sprite ) override;



};

