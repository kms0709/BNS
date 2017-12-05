#pragma once
#include "GameNode.h"


class TestScene2 : public GameNode
{
private:
	vector<SkinnedMesh*> _SMList;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();


	TestScene2();
	~TestScene2();
};

