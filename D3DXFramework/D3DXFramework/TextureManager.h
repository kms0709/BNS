#pragma once
#include "SingletonBase.h"


class TextureManager : public SingletonBase<TextureManager>
{
private:
	map<wstring, LPDIRECT3DTEXTURE9> m_texture;
	map<wstring, D3DXIMAGE_INFO> m_imageInfo;

public:
	void Init();
	void Release();

	LPDIRECT3DTEXTURE9& GetTexture( wstring filepath, OUT D3DXIMAGE_INFO * imageInfo = nullptr );
	//							x최대     y최대     x현재     y현재      x크기      y크기
	vector<D3DXVECTOR2> GetUV( float maxX, float maxY, float curX, float curY, float sizeX, float sizeY );


	TextureManager();
	~TextureManager();
};

