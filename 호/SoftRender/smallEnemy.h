#pragma once
#include "enemy.h"
class smallEnemy :public enemy
{
public:
	smallEnemy();
	~smallEnemy();


	virtual void init(D3DXVECTOR3 position, char* szFolder, char* szFilename);
	virtual void update();

	virtual void attack();
	virtual void move();
	virtual void isRota();

	inline void setScale(float s) { _scale = s; }
};

