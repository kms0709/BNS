#pragma once
#include "pattern.h"

class SkinnedMesh;

enum SMALLENEMY
{
	SM_WALK = 0,			// �ȴ°�
	SM_STAND1, SM_STAND2,	// ������ �ִ°�
	SM_RUN,					// �ٴ°�
	SM_DIE,					// �״°�
	SM_ATTK					// ����
};

enum MEDIENEMY
{
	MM_WALK = 0,			// �ȴ°�
	MM_WAIT,				// �������ִ°�
	MM_UTAK,				// �� ����
	MM_SPAWN,				// ��Ƴ��°�
	MM_RUN,					// �ٴ°�
	MM_GROGGY,				// ����? ����?
	MM_DIE,					// �״°�
	MM_ATTK3,				// ���� 3
	MM_ATTK2,				// ���� 2
	MM_ATTK1				// ���� 1
};

enum BOSS
{
	BS_WALK = 0,			// �ȴ°�
	BS_WAIT,				// ������ �ִ°�
	BS_UATK2, BS_UATK1,		// �� ���� 2, 1
	BS_RUN,					// �ٴ°�
	BS_GROGGY,				// ����
	BS_FINCH,				// ����? ����?
	BS_DIE,					// �״°�
	BS_ATTK2,				// ���� 2
	BS_ATK01				// ���� 1
};

class enemy
{
public:
	enemy();
	~enemy();

	virtual void init(D3DXVECTOR3 position, char* szFolder, char* szFilename);
	virtual void update();

	virtual void attack();
	virtual void move();
	virtual void isRota();

	inline void setScale(float s) { _scale = s; }
	inline void setRotaY(float y) { _enemy->setRotaY(y); }

	// ������ üũ�ϴ� ����, �Լ�
	GETSET(bool, _die, Die);
		
protected:

	// ������
	float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

	SkinnedMesh* _enemy;

	D3DXVECTOR3 _position;

	pattern* _rotaP;
	pattern* _moveP;
	pattern* _pattern;


	SMALLENEMY _sEnemy;
	MEDIENEMY _mEnemy;
	BOSS	_boss;

	// 
	float _time, _attackTime;
	float _scale;

	// ���� ü��
	float _hp;

	bool _attack;
	bool _start;
	bool _isRo;
	bool _move;

};

