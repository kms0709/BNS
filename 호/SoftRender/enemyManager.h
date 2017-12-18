#pragma once

#include "smallEnemy.h"
#include "mediEnemy.h"
#include "enemy.h"


class enemyManager
{
public:
	enemyManager();
	~enemyManager();

	void init();
	void update();
	void render();


private:
	vector<enemy*> _enemyVec;
};

