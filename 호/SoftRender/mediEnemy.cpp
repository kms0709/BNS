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
	// �÷��̾� �������� -10?���� �̵��ϰ� ���� ����
	// ü���� ���� ���� ���Ϸ� �������� ������ 1�� �Ϲݰ��� 2���� �������� ��


}

void mediEnemy::move()
{
}

void mediEnemy::isRota()
{
	// �÷��̾� ��ġ�� ȸ�� enemy


}
