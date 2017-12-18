#include "stdafx.h"
#include "pattern.h"


pattern::pattern()
	: _position(0, 0, 0)
	, _rotaY(0)
	, _time(0)
	, _maxTime(0)
	, end(false)
{
}


pattern::~pattern()
{
}

void pattern::start(float angle)
{
	_rotaY = angle;
	_time = 0;
	end = false;
}

void pattern::start(float angle, float endAngle)
{
}

void pattern::start(D3DXVECTOR3 position, D3DXVECTOR3 endPosition, float angle, bool run)
{
	_position = position;
	_time = 0;
	end = false;
}

void pattern::update()
{
	if (end) return;

	_time += TIMEMANAGER->getElapsedTime();

	if (_time > _maxTime) 
		end = true;

}
