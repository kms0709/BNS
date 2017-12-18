#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
	for each(auto it in _enemyVec)
	{
		//SAFE_DELETE(it);
	}
}

void enemyManager::init()
{
	char* folderName;
	folderName = "./testXFile/";


	// ¼ÒÇü¸÷
	for (int i = 0; i < 1; i++)
	{
		D3DXVECTOR3 position = D3DXVECTOR3(rand() % 100 - rand() % 100, 0, rand() % 100 - rand() % 100);
		enemy* em = new smallEnemy;
		em->init(position, "./testXFile/smallEnemy/", "smallEnemy.x");
		em->setScale(0.5f);
		em->setRotaY(float(rand()) / float(RAND_MAX) * PI2);

		_enemyVec.push_back(em);
	}

	// ÁßÇü¸÷
	enemy* medi = new mediEnemy;
	medi->init(D3DXVECTOR3(0, 0, 0), "./testXFile/mediEnemy/", "ForestGuardian.x");

	medi->setScale(1.0f);

	_enemyVec.push_back(medi);

}

void enemyManager::render()
{
	for each(auto it in _enemyVec)
	{
		it->update();
	}
}
