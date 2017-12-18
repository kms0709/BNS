#include "stdafx.h"
#include "smallEnemy.h"


smallEnemy::smallEnemy()
{
}


smallEnemy::~smallEnemy()
{
}

void smallEnemy::init(D3DXVECTOR3 position, char * szFolder, char * szFilename)
{
	enemy::init(position, szFolder, szFilename);
	_hp = 100.0f;
}

void smallEnemy::update()
{
	enemy::update();

	if (!_isRo)
	{
		_pattern = _rotaP;
		_pattern->start(_enemy->getRotaY());
		_isRo = true;
	}

	else
	{
		if (!_move)
		{
			if (_pattern->getend())
			{
				float angle = _pattern->getRotaY();

				float x = _position.x + cosf(angle) * getFromFloatTo(30.0f, 50.0f);
				float z = _position.z + -sinf(angle) * getFromFloatTo(30.0f, 50.0f);

				D3DXVECTOR3 endP = { x, _position.y, z };

				bool run = rand() % 2;

				if (run) _sEnemy = SM_RUN;
				else _sEnemy = SM_WALK;

				_pattern = _moveP;

				_pattern->start(_position, endP, angle, run);

				_move = true;
			}
			else
			{
				_enemy->setRotaY(_pattern->getRotaY());
			}
		}

		else
		{
			if (!_pattern->getend())
			{
				_position = _pattern->getPosition();
			}
			else
			{
				_isRo = false;
				_move = false;
			}
		}

		if (!_pattern->getend())
		{
			_pattern->update();
			
		}


	}

	if (_die) _sEnemy = SM_DIE;
}

void smallEnemy::attack()
{
	if (!_attack) return;

	// 현재 모션이 공격하는 모션일때
	if (_sEnemy == SM_ATTK)
	{
		// 공격모션이 끝나면
		if (_enemy->getAniEnd(_sEnemy))
		{
			// 가만히 있는 모션 2로 바꿔줌
			_sEnemy = SM_STAND2;
		}
	}

	// 가만히 있는 모션 2면
	else if (_sEnemy == SM_STAND2)
	{
		// 경직시간 ++
		_attackTime += TIMEMANAGER->getElapsedTime();

		// 경직시간이 3초 이상이 되면
		if (_attackTime >= 3.0f)
		{
			_attack = false;
			_attackTime = 0.0f;
		}
	}
}

void smallEnemy::move()
{
}

void smallEnemy::isRota()
{
}
