#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init( void )
{
	GameNode::Init( true );

	MANAGER_SCENE->AddScene( L"TestScene", new TestScene );
	MANAGER_SCENE->AddScene( L"TestScene2", new TestScene2 );
	MANAGER_SCENE->ChangeScene( L"TestScene" );

	return S_OK;
}

void MainGame::Release( void )
{
	GameNode::Release();


}

void MainGame::Update( void )
{
	GameNode::Update();
	MANAGER_SCENE->Update();

	if ( MANAGER_INPUT->IsKey( SPKL_1 ) )
	{
		MANAGER_SCENE->ChangeScene( L"TestScene" );
	}

	if ( MANAGER_INPUT->IsKey( SPKL_2 ) )
	{
		MANAGER_SCENE->ChangeScene( L"TestScene2" );
	}



}

void MainGame::Render( void )
{
//	GameNode::Render();

	MANAGER_SCENE->Render();
	

	MANAGER_TIME->Render();		// FPS와 시간 나타냄
	MANAGER_INPUT->LogRender();	// 키 입력 나타냄

}
