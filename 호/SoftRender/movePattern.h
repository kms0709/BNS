#pragma once
#include "pattern.h"

class movePattern : public pattern
{
public:
	movePattern();
	virtual ~movePattern();

	void start();
	void start(D3DXVECTOR3 position, D3DXVECTOR3 endPosition, float angle, bool run);
	void update();

private:
	float _angle;
	float _distan;
};
