#pragma once
#include "enemyManager.h"

class cubeMan;
class characterCtrl;
class OBJLoader;
class ASEcharacter;
class MaterialTexture;
class HeightMap;
class RayCtrl;
class SkinnedMesh;
class FrustumCulling;


class MainGameManager
{
	SINGLETON( MainGameManager )

	void Init ();
	void Update();
	void Render ( );
	void WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	void Destroy();


	

private:		// �Լ�
	void setLight();
	
	void makeSp();	// ���Ǿ� ����
	void spRender();	// �׷���

	void skinLoad();	// �ε�


private:		// vector
	
	//vector<Group*> groupList;
	//vector<Group*> groupList2;
	//vector<MaterialTexture*> mtList;

	vector<VertexPC> _under;
	vector<SphereInfo> _spVec;
	vector<SkinnedMesh*> _skinVec;

private:		// ������ Ŭ����
	/*characterCtrl* characterCtrl;
	OBJMap* _map;
	HeightMap* _ma;
	LinearInterpolation* lerf;*/

	SkinnedMesh* _skin;

	FrustumCulling* _frust;

private:			// Ŭ����
	CameraCtrl  cameraCtrl;
	GridCtrl    gridCtrl;


	enemyManager _enemy;

	/*Cube _cube;
	cubeMan		_cubeMan;
	
	ASEcharacter _char;	

	OBJLoader _obj;*/



private:			// ����
	D3DXVECTOR3 _position;

	LPD3DXMESH mesh = nullptr;

	LPD3DXMESH _sp;
	LPD3DXMESH _smallSp;

	D3DMATERIAL9 _spMt;
	D3DMATERIAL9 _smallSpMt;
	D3DMATERIAL9 _pickMt;

	SphereInfo _smallSpInfo;

};

