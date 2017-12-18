#pragma once
#include "pattern.h"

class SkinnedMesh;

enum SMALLENEMY
{
	SM_WALK = 0,			// 걷는거
	SM_STAND1, SM_STAND2,	// 가만히 있는거
	SM_RUN,					// 뛰는거
	SM_DIE,					// 죽는거
	SM_ATTK					// 공격
};

enum MEDIENEMY
{
	MM_WALK = 0,			// 걷는거
	MM_WAIT,				// 가만히있는거
	MM_UTAK,				// 강 공격
	MM_SPAWN,				// 살아나는거
	MM_RUN,					// 뛰는거
	MM_GROGGY,				// 스턴? 경직?
	MM_DIE,					// 죽는거
	MM_ATTK3,				// 공격 3
	MM_ATTK2,				// 공격 2
	MM_ATTK1				// 공격 1
};

enum BOSS
{
	BS_WALK = 0,			// 걷는거
	BS_WAIT,				// 가만히 있는거
	BS_UATK2, BS_UATK1,		// 강 공격 2, 1
	BS_RUN,					// 뛰는거
	BS_GROGGY,				// 경직
	BS_FINCH,				// 위협? 위험?
	BS_DIE,					// 죽는거
	BS_ATTK2,				// 공격 2
	BS_ATK01				// 공격 1
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

	// 죽은지 체크하는 변수, 함수
	GETSET(bool, _die, Die);
		
protected:

	// 랜덤값
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

	// 적의 체력
	float _hp;

	bool _attack;
	bool _start;
	bool _isRo;
	bool _move;

};

