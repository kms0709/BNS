#include "stdafx.h"
#include "UIManager.h"


UIManager::UIManager()
{
}


UIManager::~UIManager()
{
	_sprite->Release();
}

void UIManager::init()
{
	D3DXIMAGE_INFO stImageInfo;
	LPDIRECT3DTEXTURE9 pTexture = TEXTMANAGER->getTextures("UI/panel-info.png", &stImageInfo);

	_uiRoot = new uiObj;

	uiImageView* imageView = new uiImageView;
	imageView->SetTexture(pTexture);
	imageView->setLocalPos(D3DXVECTOR3(0, 0, 0));
	imageView->setSize(D3DXVECTOR2(stImageInfo.Width, stImageInfo.Height));
	imageView->setDebugRender(1);
	_uiRoot->addChild(imageView);

	uiButton* button1 = new uiButton;
	button1->setTexture("UI/btn-med-up.png", "UI/btn-med-over.png", "UI/btn-med-down.png");
	button1->setLocalPos(D3DXVECTOR3(130, 330, 0));
	button1->setButtonDelegate(this);
	button1->setTag(1);
	button1->setDebugRender(true);
	_uiRoot->addChild(button1);

	uiButton* button2 = new uiButton;
	button2->setTexture("UI/btn-med-up.png", "UI/btn-med-over.png", "UI/btn-med-down.png");
	button2->setLocalPos(D3DXVECTOR3(130, 400, 0));
	button2->setButtonDelegate(this);
	button2->setTag(2);
	button2->setDebugRender(false);
	_uiRoot->addChild(button2);

	uiTextView* txt = new uiTextView;
	txt->setLocalPos(D3DXVECTOR3(250, 200, 0));
	txt->setText("NONE");
	LPD3DXFONT font = TEXTMANAGER->getFont(TEXTMANAGER->FONT_NOMAL);
	txt->setFont(font);
	txt->setTag(3);
	_uiRoot->addChild(txt);



	D3DXCreateSprite(D3DDevice, &_sprite);

}

void UIManager::update()
{
	_uiRoot->update();
}

void UIManager::render()
{
	_uiRoot->render(_sprite);

}

void UIManager::OnClick(uiButton * pSender)
{
	char str[256];
	sprintf(str, "%d ¼±ÅÃ", (uiTextView*)pSender->getTag());
	uiTextView* txt = (uiTextView*)_uiRoot->getChildByTag(3);
	txt->setText(str);


}
