#include "stdafx.h"
#include "rotaPattern.h"


rotaPattern::rotaPattern()
{
}


rotaPattern::~rotaPattern()
{
}

void rotaPattern::start(float angle)
{
	pattern::start(angle);

	_maxTime = 1.0f;

	//	(-130 ~ 130도)
	// 130  = 180 - 50; 50 = 30 - 20
	//		  PI - PI / 9 - PI / 6;

	float a = PI - PI / 9 - PI / 6;
	_angle = getFromFloatTo(-a, a);

	if (_angle < 0.0f) _angle -= PI / 9;	// -20 ~ 20 값 이상?  -150 ~ -20, 20 ~ 150
	else _angle += PI / 9;

	
	
	if (_plusAngle * _maxTime > PI)
	{
		 
	}

	//float d = _plusAngle * _maxTime;
	//
	//float m_fFacingTarget, m_fFacing;
	//
	//m_fFacing = angle;
	//m_fFacingTarget = angle + an;
	//
	//float fFacing = m_fFacingTarget;	// 움직일 각도
	//
	//if (m_fFacingTarget > m_fFacing)
	//	fFacing -= 2 * D3DX_PI;
	//
	////			 플레이어 각도 -될 각도
	//float fDiff = m_fFacing - fFacing;
	//
	////  각도가 180도보가 작으면
	//if (fDiff < D3DX_PI) // cw turn
	//{
	//	// 플레이어 각도 - 
	//	if (m_fFacing - _plusAngle * _maxTime <= fFacing)
	//		_plusAngle = m_fFacingTarget;
	//	else
	//		_plusAngle = float(m_fFacing - _plusAngle * _maxTime);
	//}
	//// 180도 이상이면
	//else // ccw turn
	//{
	//	if (m_fFacing + _plusAngle * TIMEMANAGER->getElapsedTime() - 2 * D3DX_PI >= an)
	//		_plusAngle = m_fFacingTarget;
	//	else
	//		_plusAngle = float(m_fFacing + _plusAngle * _maxTime);
	//}
}

void rotaPattern::start(float angle, float endAngle)
{
	pattern::start(angle);
	_maxTime = 1.0f;

	_angle = endAngle - angle;

	if (_angle > PI) _angle -= PI2;

	_plusAngle = (TIMEMANAGER->getElapsedTime() / _maxTime) * _angle;

	if (_plusAngle * _maxTime > PI)
	{
		
	}


	
}

void rotaPattern::update()
{
	pattern::update();

	_plusAngle = (TIMEMANAGER->getElapsedTime() / _maxTime) * _angle;

	_rotaY += _plusAngle;

	// 360도가 넘어가면 0도로 초기화
	if (_rotaY > PI * 2)
	{
		_rotaY -= PI * 2;
	}
	else if (_rotaY < -PI * 2)
	{
		_rotaY += PI * 2;
	}
}