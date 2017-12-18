#pragma once

#define TIMEMANAGER TimeManager::GetInstance()

class TimeManager
{
	SINGLETON( TimeManager )
public:
	void Update();
	float getElapsedTime() { return _deltaTime / 1000.0f; }

private:
	DWORD _lastUpdateTime;
	DWORD _deltaTime;

};


