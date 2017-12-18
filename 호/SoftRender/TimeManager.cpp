#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
	_deltaTime = 0;
	_lastUpdateTime = GetTickCount();
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	DWORD curUpdateTime = GetTickCount();
	_deltaTime = curUpdateTime - _lastUpdateTime;
	_lastUpdateTime = curUpdateTime;
}