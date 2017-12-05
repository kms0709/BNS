#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

LPD3DXFONT FontManager::GetFont( FontType fontType )
{
	if ( fontMap.find( fontType ) == fontMap.end() )
	{
		switch ( fontType )
		{
		case FontType::CHAT:
			{

			}
			break;
		case FontType::NORMAL:
			{

			}
			break;
		case FontType::QUEST:
			{
				D3DXFONT_DESC fd;
				ZeroMemory( &fd, sizeof( LPD3DXFONT_DESC ) );

				fd.Height = 22;
				fd.Width = 0;
				fd.Weight = FW_NORMAL;
				fd.Italic = false;
				fd.CharSet = DEFAULT_CHARSET;
				fd.OutputPrecision = OUT_DEFAULT_PRECIS;
				fd.PitchAndFamily = FF_DONTCARE;
				//strcpy_s(fd.FaceName, "±º∏≤√º");	
				//AddFontResource("umberto.ttf");
				wcscpy( fd.FaceName, L"»ﬁ∏’∆Ì¡ˆ√º" );
				//strcpy(fd.FaceName, "umberto");

				D3DXCreateFontIndirect( D3DDevice, &fd, &fontMap[ fontType ] );
			}
			break;
		}
	}
	return fontMap[ fontType ];
}

void FontManager::Destroy()
{
	for each( auto fontMapIter in fontMap )
	{
		SAFE_RELEASE( fontMapIter.second );
	}
	fontMap.clear();
}