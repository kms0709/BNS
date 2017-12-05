#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<wstring, GameNode*> mapSceneList;
	typedef map<wstring, GameNode*>::iterator mapSceneIter;
private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneIter _miSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

public:
	SceneManager();
	~SceneManager();

	HRESULT Init( void );
	void Release( void );
	void Update( void );
	void Render( void );

	//¾À Ãß°¡
	GameNode* AddScene( wstring sceneName, GameNode* scene );

	//·Îµù ¾À Ãß°¡
	GameNode* AddLoadingScene( wstring loadingSceneName, GameNode* scene );

	HRESULT ChangeScene( wstring sceneName );
	HRESULT ChangeScene( wstring sceneName, wstring loadingSceneName );

	friend DWORD CALLBACK LoadingThread( LPVOID prc );

	inline GameNode* GetCurScene() { return _currentScene; }

	inline map<wstring, GameNode*> GetMap() { return _mSceneList; }
	inline map<wstring, GameNode*>::iterator GetIMap() { return _miSceneList; }

	//ÇØ´ç¾À «n
	bool SceneCheck( wstring sceneName );
};

