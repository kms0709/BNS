#include "stdafx.h"
#include "mediEnemy.h"


mediEnemy::mediEnemy()
{
}


mediEnemy::~mediEnemy()
{
}

void mediEnemy::init(D3DXVECTOR3 position, char * szFolder, char * szFilename)
{
	enemy::init(position, szFolder, szFilename);

	_hp = 300.0f;
}

void mediEnemy::update()
{
	enemy::update();
}

void mediEnemy::attack()
{
	// 플레이어 위지에서 -10?정도 이동하고 나서 공격
	// 체력이 일정 수준 이하로 떨어지면 강공격 1번 일반공격 2번을 랜덤으로 씀


}

void mediEnemy::move()
{
}

void mediEnemy::isRota()
{
	// 플레이어 위치로 회전 enemy


}
