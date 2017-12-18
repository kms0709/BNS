#include "stdafx.h"

#include "cubeMan.h"
#include "OBJLoader.h"
#include "ASEFrame.h"
#include "HeightMap.h"
#include "RayCtrl.h"
#include "SkinnedMesh.h"
#include "FrustumCulling.h"


#include "MainGameManager.h"

MainGameManager::MainGameManager()
{
}


MainGameManager::~MainGameManager()
{
}

void MainGameManager::Init()
{
	gridCtrl.Init();
	cameraCtrl.Init();

	//makeSp();
	skinLoad();
	_frust = new FrustumCulling;


	setLight();

	_enemy.init();

	/*
	_cubeMan.init();

	characterCtrl = new characterCtrl;

	lerf = new LinearInterpolation;
	lerf->Init();

	D3DXMATRIXA16 matR, matS, matWorld;
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	D3DXMatrixIdentity(&matWorld);

	matWorld = matWorld * matS;

	OBJLoader* pObjLoader = new OBJLoader;
	pObjLoader->Load("Map.obj", &matWorld, groupList);	// 건물 이미지
	pObjLoader->Load("map_surface.obj", &matWorld, groupList2); // 땅 이미지

	mesh = pObjLoader->meshLoad("Map.obj", &matWorld, mtList);


	SAFE_RELEASE(pObjLoader);

	for each (auto it in groupList)
	it->init();

	for each (auto it2 in groupList2)
	it2->init();

	_map = new OBJMap;
	_map->Load("map_surface.obj", &matWorld);


	_cube.Init(matWorld);


	_char.Load("woman/woman_01_all.ASE");

	D3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


	_cube.SetworldMat(matWorld);


	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	_cube.SetmatS(matS);
	_cube.setmaterialColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	_cube.SetPosition(*characterCtrl.GetPosition());


	_ma = new HeightMap;
	_ma->Load("HeightMapData/HeightMap.raw", &matWorld);
	_ma->SetTexture(TEXTMANAGER->getTextures("HeightMapData/terrain.jpg"));	*/

}

void MainGameManager::Update()
{
	TIMEMANAGER->Update();

	cameraCtrl.Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	_frust->Update();

	_skinVec[0]->getMatrix(_skinVec[1], nullptr, "Bip01-Spine3");
	_skinVec[0]->getMatrix(_skinVec[2], nullptr, "Bip01-Spine");
	_skinVec[2]->SetPosition(D3DXVECTOR3(0.3f, 0, 1.3f));

	/*characterCtrl->Update(_map);

	_cube.cubeUpdate(*characterCtrl->GetWorldTM());


	_char.Update(_ma);

	lerf->Update();

	_cube.SetworldMat(*characterCtrl.GetWorldTM());


	_map.GetHeight(_position.x, _position.y, _position.z);

	_cube.SetPosition(_position);
	_cube.SetrotaY(*characterCtrl.getRoteY());*/
}

void MainGameManager::Render()
{
	gridCtrl.Render();

	//for (int i = 0; i < _skinVec.size(); i++)
	//{
	//	//if (GetKeyState(VK_SPACE) & 0x8000)  _frust->IsFrustum(_skinVec[i]->GetBoundingSphere());
	//	if (_skinVec[i]->GetBoundingSphere()->isFrust) _skinVec[i]->UpdateAndRender();
	//}
	_enemy.render();

	/*lerf->Render();
	 
	for each(auto it in groupList)
	{
	it->Render();
	}

	for each(auto it in groupList2)
	{
	it->Render();
	}

	for (int i = 0; i < mtList.size(); i++)
	{
	D3DDevice->SetMaterial(&mtList[i]->GetMaterial());
	D3DDevice->SetTexture(0, mtList[i]->GetTexture());
	mesh->DrawSubset(i);
	}

	_cube.Render();

	_char.Render();
	_ma->Render();*/

	//spRender();
}

void MainGameManager::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	cameraCtrl.WndProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_RBUTTONDOWN:
	{
		RayCtrl r = RayCtrl::RayAtWorldSpace(_ptMouse.x, _ptMouse.y);

		for (int i = 0; i < _spVec.size(); i++)
		{
			_spVec[i].isPicked = r.IsPicked(&_spVec[i]);
		}
	}
	break;

	case WM_LBUTTONDOWN:
	{
		float u, v, t;
		float interX, interZ;

		interX = (_ptMouse.x - WINSIZEX / 2) / 100.0f;
		interZ = (_ptMouse.y - WINSIZEY / 2) / 100.0f;

		D3DXVECTOR3 direc = { 0.0f, -1.0f, 0.0f };
		D3DXVECTOR3 ray = { interX, 1000.0f, interZ };

		for (int i = 0; i < _under.size(); i += 3)
		{
			if (D3DXIntersectTri(&_under[i].p, &_under[i + 1].p, &_under[i + 2].p, &ray, &direc, &u, &v, &t))
			{
				_smallSpInfo.center = D3DXVECTOR3(interX, 0, interZ);
				break;
			}
		}
	}

	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			static int num = 0;

			++num;

			for (int i = 0; i < _skinVec.size(); i++)
			{
				_skinVec[i]->SetAnimationIndex(num);
			}
		}
		break;
		}
	}

	break;
	}
}

void MainGameManager::Destroy()
{
	//SAFE_RELEASE(lerf);
	//
	//for each(auto it in groupList)
	//{
	//	SAFE_RELEASE(it);
	//}
	//for each(auto it in groupList2)
	//{
	//	SAFE_RELEASE(it);
	//}

	for each(auto it in _skinVec)
	{
		SAFE_DELETE(it);
	}


	g_pSkinnedMeshManager->Destroy();

	SAFE_DELETE(_frust);
}

// 빛 설정해주는거
void MainGameManager::setLight()
{
	D3DXVECTOR3 direction(rand() % 100, -rand() % 100, rand() % 100);
	D3DXVec3Normalize(&direction, &direction);

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	light.Ambient = light.Diffuse = light.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = direction;

	D3DDevice->SetLight(0, &light);
	D3DDevice->LightEnable(0, true);
}


// sphere를 만드는곳
void MainGameManager::makeSp()
{
	_sp = nullptr;

	vector<VertexPC> ver;

	ver.resize(4);
	D3DCOLOR co = D3DCOLOR_XRGB(0xcf, 0xcf, 0xcf);

	ver[0].p = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);	// 0
	ver[0].c = co;

	ver[1].p = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);	// 4
	ver[1].c = co;

	ver[2].p = D3DXVECTOR3(10.0f, 0.0f, -10.0f);	// 3
	ver[2].c = co;

	ver[3].p = D3DXVECTOR3(10.0f, 0.0f, 10.0f);		// 7
	ver[3].c = co;

	_under.push_back(ver[1]);
	_under.push_back(ver[2]);
	_under.push_back(ver[0]);

	_under.push_back(ver[1]);
	_under.push_back(ver[3]);
	_under.push_back(ver[2]);


	D3DXCreateSphere(D3DDevice, 0.5f, 18, 10, &_smallSp, nullptr);
	D3DXCreateSphere(D3DDevice, 1.0f, 30, 10, &_sp, nullptr);

	_smallSpMt.Ambient = _smallSpMt.Diffuse = _smallSpMt.Specular = D3DXCOLOR(0.1f, 0.0f, 0.5f, 1.0f);

	SphereInfo sp;
	sp.center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sp.radi = 0.5f;
	sp.isPicked = false;

	_smallSpInfo = sp;

	_spMt.Ambient = _spMt.Diffuse = _spMt.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	_pickMt.Ambient = _pickMt.Diffuse = _pickMt.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 50; i++)
	{
		sp.center = D3DXVECTOR3(rand() % 50 - rand() % 50, rand() % 50, rand() % 50 - rand() % 50);
		sp.radi = 1.0f;
		sp.isPicked = false;

		_spVec.push_back(sp);
	}
}

void MainGameManager::spRender()
{

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	D3DDevice->SetFVF(VertexPC::FVF);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, _under.size() / 3, &_under[0], sizeof(VertexPC));

	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 transMat;

	for (int i = 0; i < _spVec.size(); i++)
	{

		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&transMat, _spVec[i].center.x, _spVec[i].center.y, _spVec[i].center.z);
		mat = mat * transMat;

		if (!_spVec[i].isPicked) D3DDevice->SetMaterial(&_spMt);
		else
		{
			D3DDevice->SetMaterial(&_pickMt);
		}

		D3DDevice->SetTransform(D3DTS_WORLD, &mat);

		_sp->DrawSubset(0);
	}

	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&transMat, _smallSpInfo.center.x, _smallSpInfo.center.y, _smallSpInfo.center.z);

	mat = cameraCtrl.getMatRotaX() * cameraCtrl.getMatRotaY() * transMat;

	D3DDevice->SetMaterial(&_smallSpMt);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	_smallSp->DrawSubset(0);
}

void MainGameManager::skinLoad()
{
	SkinnedMesh* body = new SkinnedMesh("포포/", "popori.x");
	body->SetPosition(D3DXVECTOR3(100.0f, 0, 0));
	_skinVec.push_back(body);

	SkinnedMesh* head = new SkinnedMesh("포포/", "poporiFace.x");
	//body->getMatrix(head, nullptr, "Bip01-Spine3");
	head->setScale(1.15f);
	head->SetPosition(D3DXVECTOR3(-1.0f, 0, 0.0f));
	_skinVec.push_back(head);

	SkinnedMesh* tail = new SkinnedMesh("포포/", "poporiTail.x");
	//body->getMatrix(tail, nullptr, "Bip01-Spine");
	//tail->SetPosition(D3DXVECTOR3(0, 0, 0.2f));
	tail->setScale(1.2f);
	_skinVec.push_back(tail);
}
