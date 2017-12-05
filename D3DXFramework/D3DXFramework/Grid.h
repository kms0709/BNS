#pragma once
#include "Object.h"


class Grid
{
private:
	D3DXMATRIX matrix;

	vector<LinePC> lineList;

public:
	void Init();
	void Release();
	void Update();
	void Render();


	Grid();
	~Grid();
};

