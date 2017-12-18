#include "stdafx.h"
#include "movePattern.h"


movePattern::movePattern()
{
}


movePattern::~movePattern()
{
}

void movePattern::start()
{
}

void movePattern::start(D3DXVECTOR3 position, D3DXVECTOR3 endPosition, float angle, bool run)
{
	pattern::start(position, endPosition,angle, run);

	float time = TIMEMANAGER->getElapsedTime();

	//(TIMEMANAGER->getElapsedTime() / 시간(초)) * 거리;
	_speed = (time / 1) * 5;
	if (run) _speed = _speed * 1.5f;

	_startPosition = position;
	_endPosition = endPosition;

	_distan = getDistance(D3DXVECTOR2(position.x, position.z), D3DXVECTOR2(endPosition.x, endPosition.z));
	_time = 0;
	_maxTime = time * _distan / _speed;

	_angle = angle;
}

void movePattern::update()
{
	pattern::update();

	_speed = TIMEMANAGER->getElapsedTime() / _maxTime * _distan;

	//_position.x += cosf(_angle) * _speed;
	//_position.z += -sinf(_angle) * _speed;

	D3DXVec3Lerp(&_position, &_startPosition, &_endPosition, _time);

	printf("Sx : %0.7f\n", _startPosition.x);
	printf("Sz : %0.7f\n\n", _startPosition.z);

	printf("endx : %0.7f\n", _endPosition.x);
	printf("endz : %0.7f\n\n", _endPosition.z);

	printf("x : %0.7f\n", _position.x);
	printf("z : %0.7f\n\n", _position.z);
}
