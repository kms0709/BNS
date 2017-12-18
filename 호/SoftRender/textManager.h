#pragma once

class textManager
{
	SINGLETON(textManager)

public:
	enum FONTTYPE
	{
		FONT_NOMAL,
		FONT_ELSE,
		FONT_NONE
	};

	LPDIRECT3DTEXTURE9 getTextures(const char * fullPath, OUT D3DXIMAGE_INFO* imageInfo = nullptr);
	LPDIRECT3DTEXTURE9 getTextures(string fileName, OUT D3DXIMAGE_INFO* imageInfo = nullptr);
	LPD3DXFONT getFont(FONTTYPE font);
private:

	typedef map<string, LPDIRECT3DTEXTURE9> textures;
	typedef map<string, D3DXIMAGE_INFO> imageInfo;

	typedef map<FONTTYPE, LPD3DXFONT> font;

	textures _textList;
	imageInfo _imageInfo;
	font _font;
};


#define TEXTMANAGER textManager::GetInstance()
