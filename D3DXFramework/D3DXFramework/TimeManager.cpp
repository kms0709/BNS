#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
	: _timer( NULL )
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
	_timer = new Timer;
	_timer->Init();

	TimerFont = MANAGER_FONT->GetFont( FontManager::QUEST );

	return S_OK;
}

void TimeManager::Release()
{
	if ( _timer != NULL )
	{
		SAFE_DELETE( _timer );
		_timer = NULL;
	}
}

void TimeManager::Update( float lock )
{
	if ( _timer != NULL )
	{
		_timer->Tick( lock );
	}
}

void TimeManager::Render()
{
	// D3DX 에 맞게 변경

	//string frameRate;
	//SetBkMode(hdc, TRANSPARENT);
	//TRANSPARENT : 폰트 뒷배경 투명
	//OPAQUE : 폰트 뒷배경 불투명

	RECT rc;


#ifdef _DEBUG
	{
		wstring wstr;
		wchar_t str[ 256 ];

		//FPS
		swprintf_s( str, L"framePerSec(FPS) : %d", _timer->GetFrameRate() );
		wstr = str;

		SetRect( &rc, 0, g_ClientRC.bottom - 60, 300, 100 );
		TimerFont->DrawText( nullptr,
			wstr.c_str(),
			wstr.length(),
			&rc,
			textFormat,
			color );

		//WorldTime
		swprintf_s( str, L"worldTime : %f", _timer->GetWorldTime() );
		wstr = str;
		SetRect( &rc, 0, g_ClientRC.bottom - 40, 300, 100 );
		TimerFont->DrawText( nullptr,
			wstr.c_str(),
			wstr.length(),
			&rc,
			textFormat,
			color );

		//ElapsedTime
		swprintf_s( str, L"elaspedTime : %f", _timer->GetElapsedTime() );
		wstr = str;
		SetRect( &rc, 0, g_ClientRC.bottom - 20, 300, 100 );
		TimerFont->DrawText( nullptr,
			wstr.c_str(),
			wstr.length(),
			&rc,
			textFormat,
			color );
	}
#endif
}


