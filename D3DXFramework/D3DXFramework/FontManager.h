#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	enum FontType
	{
		NORMAL,
		CHAT,
		QUEST,
	};

private:
	map<FontType, LPD3DXFONT> fontMap;

public:
	LPD3DXFONT GetFont( FontType fontType );
	void Destroy();

	FontManager();
	~FontManager();
};

