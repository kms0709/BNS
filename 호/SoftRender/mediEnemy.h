#pragma once
#include "enemy.h"
class mediEnemy : public enemy
{
public:
	mediEnemy();
	~mediEnemy();

	virtual void init(D3DXVECTOR3 position, char* szFolder, char* szFilename);
	virtual void update();

	virtual void attack();
	virtual void move();
	virtual void isRota();
};

