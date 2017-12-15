#include "stdafx.h"
#include "TestScene.h"
#include "PlayerModel.h"
#include "CharacterCtrl.h"


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

	pModel = new PlayerModel;
	pModel->Init();
	Ctrl = new CharacterCtrl;
	Ctrl->Init();

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

	SAFE_RELEASE( pModel );
}

void TestScene::Update()
{
//	_popori[ 1 ]->SetMatrices( _popori[ 0 ]->GetRoot(), "Bip01-Spine3");
//	_popori[ 1 ]->SetBone( _popori[ 0 ]->GetRoot(), "Bip01-Spine3", "Dummy_Spine3" );
//	_popori[ 1 ]->SetBone( _popori[ 0 ]->GetRoot(), "Bip01-Neck", "Dummy_Neck" );

	Ctrl->Update();
	pModel->Update();
	pModel->SetMatWorld( Ctrl->GetMatrix() );

}

void TestScene::Render()
{
	

//	D3DXMatrixScaling( &worldMat, 0.01f, 0.01f, 0.01f );
//	D3DDevice->SetTransform( D3DTS_WORLD, &worldMat );

//	for each ( auto p in mapGroup )
//		p->Render();

	pModel->Render();

	grid->Render();
}
