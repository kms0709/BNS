#include "stdafx.h"
#include "uiImageView.h"

uiImageView::uiImageView()
{
}

uiImageView::~uiImageView()
{
}

void uiImageView::render(LPD3DXSPRITE sprite)
{
	if (!texture) return;

	RECT rc;
	SetRect(&rc, 0, 0, size.x, size.y);

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	sprite->SetTransform(&worldMatrix);

	sprite->Draw(texture, &rc, NULL, &getLocalPos(), color);

	sprite->End();
}
