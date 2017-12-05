#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::Init()
{
}

void TextureManager::Release()
{
	for each( auto iter in m_texture )
	{
		SAFE_RELEASE( iter.second );
	}
	m_texture.clear();
	m_imageInfo.clear();
}

LPDIRECT3DTEXTURE9& TextureManager::GetTexture( wstring filepath, OUT D3DXIMAGE_INFO * imageInfo )
{
	if ( imageInfo )
	{
		if ( m_texture.find( filepath ) == m_texture.end() ||
			m_imageInfo.find( filepath ) == m_imageInfo.end() )
		{
			SAFE_RELEASE( m_texture[ filepath ] );

			if ( FAILED( D3DXCreateTextureFromFileEx(
				D3DDevice,
				filepath.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				0,// D3DCOLOR_XRGB(255, 255, 255)
				&m_imageInfo[ filepath ],
				NULL,
				&m_texture[ filepath ] ) ) )
			{
				wchar_t str[ 64 ];
				wsprintf( str, L"%s 이미지 찾기 실패!", filepath.c_str() );
				::MessageBox( g_hWnd, str, 0, 0 );
			}
		}
		*imageInfo = m_imageInfo[ filepath ];
	}
	else
	{
		if ( m_texture.find( filepath ) == m_texture.end() )
		{
			if ( FAILED( D3DXCreateTextureFromFile(
				D3DDevice,
				filepath.c_str(),
				&m_texture[ filepath ] ) ) )
			{
				wchar_t str[ 32 ];
				wsprintf( str, L"%s 이미지 찾기 실패!", filepath );
				::MessageBox( g_hWnd, str, 0, 0 );
			}

			//			m_texture.insert( pair<wstring, LPDIRECT3DTEXTURE9>( filepath, tempTexture ) );
		}
	}

	return m_texture[ filepath ];
}

vector<D3DXVECTOR2> TextureManager::GetUV( float maxX, float maxY, float curX, float curY, float sizeX, float sizeY )
{
	vector<D3DXVECTOR2> tempList;

	tempList.push_back( D3DXVECTOR2( ( curX / maxX ), ( ( sizeY + curY ) / maxY ) ) );
	tempList.push_back( D3DXVECTOR2( ( curX / maxX ), ( curY / maxY ) ) );
	tempList.push_back( D3DXVECTOR2( ( ( sizeX + curX ) / maxX ), ( curY / maxY ) ) );
	tempList.push_back( D3DXVECTOR2( ( ( sizeX + curX ) / maxX ), ( ( sizeY + curY ) / maxY ) ) );

	return tempList;
}
