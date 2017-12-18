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

	// �ٸ� �ִϸ��̼����� �Ѿ�� �ð�
	_time = 0;
	// �����ϰ� ����? �ð�
	_attackTime = 0;

	// ���� �ִ���
	_isRo = false;
	// ���� ����
	_attack = false;
	// ������
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
	// �ִϸ��̼� ��ȣ �����ְ� �׷���
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
