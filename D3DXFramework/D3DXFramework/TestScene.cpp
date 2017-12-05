#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	MANAGER_SOUND->AddSound( L"test", L"./data/test/soundtest.wav", true, true );
	//	MANAGER_SOUND->Play( L"test" );

	D3DXMatrixIdentity( &worldMat );

//	ObjLoader* objLoader = new ObjLoader;
//	objLoader->LoadObj( L"./data/test/", L"TeraMapBeta01.obj", &worldMat, mapGroup );
	
//	SAFE_DELETE( objLoader );

	grid = new Grid;
	grid->Init();

	ZeroMemory( &m_light, sizeof( D3DLIGHT9 ) );
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_light.Ambient = D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );
	m_light.Specular = D3DXCOLOR( 0.3f, 0.3f, 0.3f, 1.0f );
	m_light.Direction = D3DXVECTOR3( 0, 1, 0 );

	D3DDevice->SetLight( 0, &m_light );
	D3DDevice->LightEnable( 0, TRUE );

	return S_OK;
}

void TestScene::Release()
{
	SAFE_RELEASE( grid );
//	for each ( auto p in mapGroup )
//	{
//		SAFE_RELEASE( p );
//	}
}

void TestScene::Update()
{

}

void TestScene::Render()
{
	

//	D3DXMatrixScaling( &worldMat, 0.01f, 0.01f, 0.01f );
//	D3DDevice->SetTransform( D3DTS_WORLD, &worldMat );

//	for each ( auto p in mapGroup )
//		p->Render();

	grid->Render();
}
