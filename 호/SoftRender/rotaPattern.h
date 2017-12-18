#pragma once
#include "pattern.h"

class rotaPattern : public pattern
{
public:
	rotaPattern();
	~rotaPattern();

	virtual void start(float angle);
	virtual void start(float angle, float endAngle);
	virtual void update();

private:
	float _plusAngle;
	float _angle;
};

