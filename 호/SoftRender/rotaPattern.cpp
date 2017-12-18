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

	//	(-130 ~ 130��)
	// 130  = 180 - 50; 50 = 30 - 20
	//		  PI - PI / 9 - PI / 6;

	float a = PI - PI / 9 - PI / 6;
	_angle = getFromFloatTo(-a, a);

	if (_angle < 0.0f) _angle -= PI / 9;	// -20 ~ 20 �� �̻�?  -150 ~ -20, 20 ~ 150
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
	//float fFacing = m_fFacingTarget;	// ������ ����
	//
	//if (m_fFacingTarget > m_fFacing)
	//	fFacing -= 2 * D3DX_PI;
	//
	////			 �÷��̾� ���� -�� ����
	//float fDiff = m_fFacing - fFacing;
	//
	////  ������ 180������ ������
	//if (fDiff < D3DX_PI) // cw turn
	//{
	//	// �÷��̾� ���� - 
	//	if (m_fFacing - _plusAngle * _maxTime <= fFacing)
	//		_plusAngle = m_fFacingTarget;
	//	else
	//		_plusAngle = float(m_fFacing - _plusAngle * _maxTime);
	//}
	//// 180�� �̻��̸�
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

	// 360���� �Ѿ�� 0���� �ʱ�ȭ
	if (_rotaY > PI * 2)
	{
		_rotaY -= PI * 2;
	}
	else if (_rotaY < -PI * 2)
	{
		_rotaY += PI * 2;
	}
}