#include "stdafx.h"

#include "uiButton.h"

uiButton::uiButton()
{
}

uiButton::~uiButton()
{
}

void uiButton::setTexture(string normal, string mouseover, string selected)
{
	D3DXIMAGE_INFO imageInfo;
	textures[BUTTON_NORMAL] = TEXTMANAGER->getTextures(normal, &imageInfo);
	textures[BUTTON_ON] = TEXTMANAGER->getTextures(mouseover, &imageInfo);
	textures[BUTTON_SELECT] = TEXTMANAGER->getTextures(selected, &imageInfo);

	setSize(D3DXVECTOR2(imageInfo.Width, imageInfo.Height));
}

void uiButton::update()
{
	RECT rc = { localPos.x, localPos.y, localPos.x + size.x, localPos.y + size.y };

	if (PtInRect(&rc, _ptMouse))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			buttonState = BUTTON_SELECT;

			if (buttonDelegate) buttonDelegate->OnClick(this);
		}
		else  buttonState = BUTTON_ON;

	}
	else buttonState = BUTTON_NORMAL;


}

void uiButton::render(LPD3DXSPRITE sprite)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rc = { 0, 0, size.x, size.y };
	sprite->Draw(textures[buttonState], &rc, 0,
		&getLocalPos(), D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}
