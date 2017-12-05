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
	//							x�ִ�     y�ִ�     x����     y����      xũ��      yũ��
	vector<D3DXVECTOR2> GetUV( float maxX, float maxY, float curX, float curY, float sizeX, float sizeY );


	TextureManager();
	~TextureManager();
};

