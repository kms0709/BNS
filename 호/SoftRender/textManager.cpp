#include "stdafx.h"
#include "textManager.h"



textManager::textManager()
{
}


textManager::~textManager()
{
	if (!_textList.empty())
	{
		for each(auto iter in _textList)
		{
			iter.second->Release();
		}

		_textList.clear();
	}
}

LPDIRECT3DTEXTURE9 textManager::getTextures(const char * fullPath, OUT D3DXIMAGE_INFO * imageInfo)
{
	return getTextures(string(fullPath), imageInfo);
}

LPDIRECT3DTEXTURE9 textManager::getTextures(string fileName, OUT D3DXIMAGE_INFO* image)
{
	if (image)
	{
		if (_textList.find(fileName) == _textList.end() || _imageInfo.find(fileName) == _imageInfo.end())
		{
			SAFE_RELEASE(_textList[fileName]);
		
			D3DXCreateTextureFromFileExA(
				D3DDevice, fileName.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				0,
				&_imageInfo[fileName], NULL,
				&_textList[fileName]);
		}

		*image = _imageInfo[fileName];
	}
	else
	{
		if (_textList.find(fileName) == _textList.end())
		{
			D3DXCreateTextureFromFileA(
				D3DDevice, fileName.c_str(),
				&_textList[fileName]
			);
		}
	}
	

	return _textList[fileName];
}

LPD3DXFONT textManager::getFont(FONTTYPE font)
{

	if (_font.find(font) == _font.end())
	{
		D3DXFONT_DESC fn;
		ZeroMemory(&fn, sizeof(D3DXFONT_DESC));

		fn.Height = 25;
		fn.Width = 10;
		fn.Weight = FW_NORMAL;
		fn.Italic = false;
		fn.CharSet = DEFAULT_CHARSET;
		fn.OutputPrecision = OUT_DEFAULT_PRECIS;
		fn.PitchAndFamily = FF_DONTCARE;

		
		switch (font)
		{
		case textManager::FONT_NOMAL:
			wcscpy(fn.FaceName, L"µ¸¿òÃ¼");

			break;

		case textManager::FONT_ELSE:
			wcscpy(fn.FaceName, L"±¼¸²Ã¼");

			break;

		case textManager::FONT_NONE:
			wcscpy(fn.FaceName, L"±Ã¼­");

			break;
		default:
			wcscpy(fn.FaceName, L"±Ã¼­Ã¼");
			break;
		}
		D3DXCreateFontIndirect(D3DDevice, &fn, &_font[font]);
	}


	return _font[font];
}
