
#pragma once

class uiTextView : public uiObj
{
public:
	uiTextView();
	virtual ~uiTextView();
	virtual void render( LPD3DXSPRITE sprite ) override;

	GETSET(string, text, Text );
	GETSET( DWORD, textFormat, TextFormat );
	GETSET( DWORD, color, Color );
	//GETSET_ADD_REF( LPD3DXFONT, font, Font );
	GETSET( LPD3DXFONT, font, Font );	


};

