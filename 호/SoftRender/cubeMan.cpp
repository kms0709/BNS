#include "stdafx.h"
#include "cubeMan.h"


cubeMan::cubeMan()
{
}


cubeMan::~cubeMan()
{
}

void cubeMan::SetTextureVertex(vector<D3DXVECTOR2>& UVList, vector<D3DXVECTOR2> UVIndex)
{
	UVList.push_back(D3DXVECTOR2(UVIndex[0].x / 16.0f, UVIndex[0].y / 8.0f));
	UVList.push_back(D3DXVECTOR2(UVIndex[1].x / 16.0f, UVIndex[1].y / 8.0f));
	UVList.push_back(D3DXVECTOR2(UVIndex[2].x / 16.0f, UVIndex[2].y / 8.0f));

	UVList.push_back(D3DXVECTOR2(UVIndex[0].x / 16.0f, UVIndex[0].y / 8.0f));
	UVList.push_back(D3DXVECTOR2(UVIndex[2].x / 16.0f, UVIndex[2].y / 8.0f));
	UVList.push_back(D3DXVECTOR2(UVIndex[3].x / 16.0f, UVIndex[3].y / 8.0f));
}

void cubeMan::init(void)
{
	_text = TEXTMANAGER->getTextures("naked.png", nullptr);


	D3DXMATRIXA16 scaleMatrix, translationMatrix, relativeResult;
	D3DXMatrixIdentity(&translationMatrix);
	std::vector<D3DXVECTOR2> UVList;
	std::vector<D3DXVECTOR2> UVIndexList;


	// 큐브맨 몸통 (루트)
	UVIndexList.push_back(D3DXVECTOR2(8, 8));
	UVIndexList.push_back(D3DXVECTOR2(8, 5));
	UVIndexList.push_back(D3DXVECTOR2(10, 5));
	UVIndexList.push_back(D3DXVECTOR2(10, 8));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();
	UVIndexList.push_back(D3DXVECTOR2(5, 8));
	UVIndexList.push_back(D3DXVECTOR2(5, 5));
	UVIndexList.push_back(D3DXVECTOR2(7, 5));
	UVIndexList.push_back(D3DXVECTOR2(7, 8));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();
	UVIndexList.push_back(D3DXVECTOR2(7, 8));
	UVIndexList.push_back(D3DXVECTOR2(7, 5));
	UVIndexList.push_back(D3DXVECTOR2(8, 5));
	UVIndexList.push_back(D3DXVECTOR2(8, 8));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();
	UVIndexList.push_back(D3DXVECTOR2(4, 8));
	UVIndexList.push_back(D3DXVECTOR2(4, 5));
	UVIndexList.push_back(D3DXVECTOR2(5, 5));
	UVIndexList.push_back(D3DXVECTOR2(5, 8));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();
	UVIndexList.push_back(D3DXVECTOR2(5, 5));
	UVIndexList.push_back(D3DXVECTOR2(5, 4));
	UVIndexList.push_back(D3DXVECTOR2(7, 4));
	UVIndexList.push_back(D3DXVECTOR2(7, 5));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();
	UVIndexList.push_back(D3DXVECTOR2(7, 4));
	UVIndexList.push_back(D3DXVECTOR2(7, 5));
	UVIndexList.push_back(D3DXVECTOR2(9, 5));
	UVIndexList.push_back(D3DXVECTOR2(9, 4));
	SetTextureVertex(UVList, UVIndexList);
	UVIndexList.clear();

	D3DXMatrixScaling(&scaleMatrix, 1.0f, 1.5f, 1.0f);
	relativeResult = scaleMatrix * translationMatrix;
//	_cube.Init();
	UVList.clear();

}

void cubeMan::update(D3DXMATRIXA16& parentWorldMatrix)
{
	//_cube.Update(parentWorldMatrix);
}

void cubeMan::render()
{
	D3DDevice->SetTexture(0, _text);
	//_cube.Render();
}
