#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"


DWORD CALLBACK LoadingThread( LPVOID prc )
{

	// 교체 준비된 씬을 초기화
	SceneManager::_readyScene->Init();

	// 현재 씬에 교체
	SceneManager::_currentScene = SceneManager::_readyScene;

	SceneManager::_loadingScene->Release();
	SceneManager::_loadingScene = NULL;
	SceneManager::_readyScene = NULL;
	
	return 0;
}

GameNode* SceneManager::_currentScene = NULL;
GameNode* SceneManager::_loadingScene = NULL;
GameNode* SceneManager::_readyScene = NULL;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init( void )
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;


	return S_OK;
}

void SceneManager::Release( void )
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for ( ; miSceneList != _mSceneList.end();)
	{
		if ( miSceneList->second != NULL )
		{
			if ( miSceneList->second == _currentScene ) miSceneList->second->Release();

			SAFE_DELETE( miSceneList->second );

			miSceneList = _mSceneList.erase( miSceneList );
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void SceneManager::Update( void )
{
	if ( _currentScene ) _currentScene->Update();
}

void SceneManager::Render( void )
{
	if ( _currentScene ) _currentScene->Render();
}

GameNode * SceneManager::AddScene( wstring sceneName, GameNode * scene )
{
	//해당 씬이 존재치 않으면 널 반환
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( sceneName, scene ) );

	return scene;
}

GameNode * SceneManager::AddLoadingScene( wstring loadingSceneName, GameNode * scene )
{
	//해당 씬이 존재치 않으면 널 반환
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( loadingSceneName, scene ) );

	return scene;
}

HRESULT SceneManager::ChangeScene( wstring sceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	//씬이 존재하지 않으면 실패를 알려줘라
	if ( find == _mSceneList.end() ) return E_FAIL;

	//찾은 씬이 현재씬이면 바꾸지 않는다
	if ( find->second == _currentScene ) return S_OK;

	//씬 전환이 성공하면~
	if ( SUCCEEDED( find->second->Init() ) )
	{
		//순서가 마음에 안들면 먼저 씬을 바꾸고, 그 전에 씬에 데이터를 날려주는
		//형태로 바꿔도 상관없다.

		if ( _currentScene ) _currentScene->Release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene( wstring sceneName, wstring loadingSceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	//씬이 존재하지 않으면 실패를 알려줘라
	if ( find == _mSceneList.end() ) return E_FAIL;

	//찾은 씬이 현재씬이면 바꾸지 않는다
	if ( find->second == _currentScene ) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find( loadingSceneName );

	if ( find == _mLoadingSceneList.end() ) return ChangeScene( loadingSceneName );

	//씬 전환이 성공하면~
	if ( SUCCEEDED( find->second->Init() ) )
	{
		if ( _currentScene ) _currentScene->Release();

		_loadingScene = findLoading->second;

		_readyScene = find->second;

		CloseHandle( CreateThread( NULL, 0, LoadingThread, NULL, 0, &_loadingThreadID ) );

	}

	return E_FAIL;
}

bool SceneManager::SceneCheck( wstring sceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	if ( find == _mSceneList.end() ) return false;
	if ( find->second == _currentScene ) return true;
	else return false;
}
