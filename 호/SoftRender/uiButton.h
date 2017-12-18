#pragma once

class uiButton;

class iUIButtonDelegate
{
public:
	virtual void OnClick(uiButton* pSender ) = 0;
};


class uiButton : public uiObj
{
public:
	uiButton();
	virtual ~uiButton();

	virtual void setTexture(string normal, string mouseover, string selected );
	virtual void update() override;
	virtual void render( LPD3DXSPRITE sprite ) override;


	enum BUTTONSTAT
	{
		BUTTON_NORMAL,
		BUTTON_ON,
		BUTTON_SELECT,
		STATE_MAX,
	};

	BUTTONSTAT buttonState;
	LPDIRECT3DTEXTURE9 textures[BUTTONSTAT::STATE_MAX];

	GETSET( iUIButtonDelegate*, buttonDelegate, ButtonDelegate );


};

