#pragma once
#include "SingletonBase.h"

#include "inc/fmod.hpp"
#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 50
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<wstring, Sound**> arrSounds;
	typedef map<wstring, Sound**>::iterator arrSoundsIter;
	typedef map<wstring, Channel**> arrChannels;
	typedef map<wstring, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT Init();
	void Release();
	void Update();

	void AddSound( wstring keyName, wstring soundName, bool bgm, bool loop );
	void Play( wstring keyName, float volume = 1.0f ); //0.0 ~ 1.0 == 0 ~ 255
	void Stop( wstring keyName );
	void Pause( wstring keyName );
	void Resume( wstring keyName );

	bool IsPlaySound( wstring keyName );
	bool IsPauseSound( wstring keyName );



	SoundManager();
	~SoundManager();
};

