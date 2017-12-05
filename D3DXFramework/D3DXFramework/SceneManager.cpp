#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"


DWORD CALLBACK LoadingThread( LPVOID prc )
{

	// ��ü �غ�� ���� �ʱ�ȭ
	SceneManager::_readyScene->Init();

	// ���� ���� ��ü
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
	//�ش� ���� ����ġ ������ �� ��ȯ
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( sceneName, scene ) );

	return scene;
}

GameNode * SceneManager::AddLoadingScene( wstring loadingSceneName, GameNode * scene )
{
	//�ش� ���� ����ġ ������ �� ��ȯ
	if ( !scene ) return NULL;

	_mSceneList.insert( make_pair( loadingSceneName, scene ) );

	return scene;
}

HRESULT SceneManager::ChangeScene( wstring sceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	//���� �������� ������ ���и� �˷����
	if ( find == _mSceneList.end() ) return E_FAIL;

	//ã�� ���� ������̸� �ٲ��� �ʴ´�
	if ( find->second == _currentScene ) return S_OK;

	//�� ��ȯ�� �����ϸ�~
	if ( SUCCEEDED( find->second->Init() ) )
	{
		//������ ������ �ȵ�� ���� ���� �ٲٰ�, �� ���� ���� �����͸� �����ִ�
		//���·� �ٲ㵵 �������.

		if ( _currentScene ) _currentScene->Release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene( wstring sceneName, wstring loadingSceneName )
{
	mapSceneIter find = _mSceneList.find( sceneName );

	//���� �������� ������ ���и� �˷����
	if ( find == _mSceneList.end() ) return E_FAIL;

	//ã�� ���� ������̸� �ٲ��� �ʴ´�
	if ( find->second == _currentScene ) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find( loadingSceneName );

	if ( find == _mLoadingSceneList.end() ) return ChangeScene( loadingSceneName );

	//�� ��ȯ�� �����ϸ�~
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
