#include "stdafx.h"
#include "uiTextView.h"

uiTextView::uiTextView()
{
}

uiTextView::~uiTextView()
{
}

void uiTextView::render(LPD3DXSPRITE sprite)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc = { localPos.x, localPos.y, localPos.x + size.x, localPos.y + size.y };
	font->DrawTextA(sprite, text.c_str(), text.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	
	sprite->End();
}
