#include "stdafx.h"

#include "SkinnedMesh.h"
#include "movePattern.h"
#include "rotaPattern.h"
#include "pattern.h"

#include "enemy.h"

enemy::enemy()
{
}


enemy::~enemy()
{
	SAFE_DELETE(_enemy);
	SAFE_DELETE(_moveP);
	SAFE_DELETE(_rotaP);
	SAFE_DELETE(_pattern);
}

void enemy::init(D3DXVECTOR3 position, char* szFolder, char* szFilename)
{
	_position = position;
	_sEnemy = SM_STAND1;

	_enemy = new SkinnedMesh(szFolder, szFilename);
	_enemy->SetPosition(position);
	
	_moveP = new movePattern;
	_rotaP = new rotaPattern;
	_pattern = _rotaP;

	_pattern->setend(true);

	// 다른 애니메이션으로 넘어가는 시간
	_time = 0;
	// 공격하고 경직? 시간
	_attackTime = 0;

	// 돌고 있는지
	_isRo = false;
	// 공격 한지
	_attack = false;
	// 안죽음
	_die = false;
	_move = false;
}

void enemy::update()
{	
	if (!_die)
	{
		if (_attack) attack();

		else
		{
			isRota();
			move();
		}
	}

	if (_hp <= 0.0f)
	{
		_die = true;
		if (_enemy->getAniEnd(SM_DIE))
		{
			_enemy->setAniStop(true);
		}
	}


	_enemy->SetPosition(_position);
	_enemy->setScale(_scale);
	// 애니메이션 번호 정해주고 그려줌
	_enemy->SetAnimationIndex(_sEnemy);
	_enemy->UpdateAndRender();
}

void enemy::attack()
{
	
}

void enemy::move()
{
}

void enemy::isRota()
{
	
}
