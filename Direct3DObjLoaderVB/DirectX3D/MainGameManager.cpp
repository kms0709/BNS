#include "stdafx.h"

#include "CubeCtrl.h"
#include "OBJLoader.h"
#include "Group.h"
#include "iMap.h"
#include "OBJMap.h"

#include "MainGameManager.h"

MainGameManager::MainGameManager ()
{
}


MainGameManager::~MainGameManager ()
{

}

void MainGameManager::Init ()
{	
	cameraCtrl.Init ();
	gridCtrl.Init ();
	//uiManager.Init();

	//lerp = new LinearInterpolation;
	//lerp->Init();

	D3DXMATRIXA16 matR, matS, matWorld;
	//D3DXMatrixRotationX ( &matR, (D3DX_PI ) );
	D3DXMatrixRotationX(&matR, (-D3DX_PI / 2.0f));
	D3DXMatrixScaling ( &matS, 1.0f, 1.0f, 1.0f);
	matWorld = matS * matR;

	//0.001f
	//0.1f
	//1.0f
	OBJLoader* pObjLoader = new OBJLoader();
	//pObjLoader->Load ( "obj/TeraMapBeta01.obj", &matWorld, groupList );
	//pObjLoader->Load("obj/TestBox2.obj", &matWorld, groupList);
	//D3DXMatrixRotationX(&matR, (-D3DX_PI/2.0f));
	D3DXMatrixRotationX(&matR, (D3DX_PI-3.14f));
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	matWorld = matS * matR;
	//pObjLoader->Load("obj/Map.obj", &matWorld, groupList);
	//
	//pObjLoader->Load("obj/TeraMapBeta01.obj", &matWorld, groupList);
	pObjLoader->Load("testMap.obj", &matWorld, groupList);
	//pObjLoader->Load ( "obj/map_surface.obj", &matWorld, groupList2 );
	SAFE_RELEASE ( pObjLoader );

	cubeCtrl = new CubeCtrl();
	cubeCtrl->Init ( &matWorld );

	//OBJMap* pMap = new OBJMap;
	//pMap->Load ( "obj/map_surface.obj", &matWorld );	
	//mapObject = pMap;
	//f
	int num = 0;
	SetLight ();

	D3DDevice->SetRenderState ( D3DRS_NORMALIZENORMALS, true );
	D3DDevice->SetRenderState ( D3DRS_LIGHTING, true );
	//D3DDevice->SetRenderState ( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
}

void MainGameManager::Update ()
{
	g_pTimeManager->Update();

	//characterCtrl.Update (mapObject);
	
	cameraCtrl.Update ( *characterCtrl.GetPosition() );
	//uiManager.Update();
	//lerp->Update();
}

void MainGameManager::Render (  )
{
	gridCtrl.Render ();		
	//uiManager.Render();
	//lerp->Render();


	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity ( &matWorld );

	D3DDevice->SetTransform ( D3DTS_WORLD, &matWorld );

	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if ( GetKeyState ( VK_SPACE ) & 0x8000 )
	{
		for each( auto p in groupList2 )
		{
			p->Render ();
		}
	}
	else
	{
		for each( auto p in groupList )
		{
			p->Render ();
		}
	}

	if ( cubeCtrl )
		cubeCtrl->Render ( characterCtrl.GetWorldTM () );


}

void MainGameManager::WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	cameraCtrl.WndProc ( hWnd, msg, wParam, lParam );
}

void MainGameManager::Destroy()
{
	
	//SAFE_RELEASE( lerp );
	//uiManager.Destroy();

	SAFE_RELEASE ( cubeCtrl );

	for each( auto p in  groupList ) {
		SAFE_RELEASE ( p );
	}
	
	for each( auto p in  groupList2 ) {
		SAFE_RELEASE ( p );
	}

}

void MainGameManager::SetLight ()
{
	D3DXVECTOR3 direction ( rand () % 100, rand () % 100, rand () % 100 );
	D3DXVec3Normalize ( &direction, &direction );

	D3DLIGHT9 light;
	ZeroMemory ( &light, sizeof ( D3DLIGHT9 ) );

	light.Ambient = light.Diffuse = light.Specular = D3DXCOLOR ( 0.8f, 0.8f, 0.8f, 1.0f );
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = direction;


	D3DDevice->SetLight ( 0, &light );
	D3DDevice->LightEnable ( 0, true );

}





