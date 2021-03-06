#pragma once
#include "GameNode.h"
#include "Grid.h"
#include "ObjLoader.h"

class PlayerModel;
class CharacterCtrl;

class TestScene : public GameNode
{
private:

	PlayerModel* pModel;
	CharacterCtrl* Ctrl;
	
	Grid* grid;

	D3DXMATRIX worldMat;
	vector<Group*> mapGroup;
	D3DLIGHT9 m_light;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();


	TestScene();
	~TestScene();
};

