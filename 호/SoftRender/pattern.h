#pragma once

class pattern
{
public:
	pattern();
	~pattern();

	// 현재 위치
	virtual void start(float angle);
	virtual void start(float angle, float endAngle);
	virtual void start(D3DXVECTOR3 position, D3DXVECTOR3 endPosition, float angle, bool run);
	virtual void update();

	inline D3DXMATRIXA16 getWorldMat() { return _worldMat; }
	inline D3DXVECTOR3 getPosition() { return _position; }

	inline float getRotaY() { return _rotaY; }

	GETSET(bool, end, end);

protected:

	float getDistance(D3DXVECTOR2 startPosition, D3DXVECTOR2 endPosition)
	{
		float x = endPosition.x - startPosition.x;
		float z = endPosition.y - startPosition.y;

		return sqrtf(x * x + z * z);
	}

	float getAngle(D3DXVECTOR3 startPosition, D3DXVECTOR3 endPosition)
	{
		float a = acosf(D3DXVec3Dot(&startPosition, &endPosition));


		//float x = endPosition.x - startPosition.x;
		//float y = endPosition.z - startPosition.z;
		//
		//float distance = sqrtf(x * x + y * y);
		//
		//float angle = acosf(x / distance);
		//
		//if (endPosition.z > startPosition.z)
		//{
		//	angle = PI * 2 - angle;
		//
		//	if (angle >= PI * 2) angle -= PI * 2;
		//}

		return a;
	}

	float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

	D3DXMATRIXA16 _worldMat;

	D3DXVECTOR3 _position, _startPosition, _endPosition;

	float _speed;	// 이동 속도
	float _rotaY;				// 회전 값
	float _time, _maxTime;		// 진행되는 시간, 실행 되는 시간
	
};

