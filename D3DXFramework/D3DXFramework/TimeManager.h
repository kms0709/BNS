#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* _timer;

	LPD3DXFONT TimerFont;
	DWORD textFormat = DT_LEFT | DT_TOP | DT_NOCLIP;
	DWORD color = D3DCOLOR_XRGB( 255, 255, 255 );

public:
	HRESULT Init();
	void Release();
	void Update( float lock = 0.0f );
	void Render();

	inline float GetElapsedTime( void ) const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime( void ) const { return _timer->GetWorldTime(); }


	TimeManager();
	~TimeManager();
};

