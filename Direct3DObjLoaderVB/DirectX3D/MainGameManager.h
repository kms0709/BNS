#pragma once

//class CubeCtrl;
class CubeMan;
class CameraCtrl;
class GridCtrl;
class CharacterCtrl;
class LinearInterpolation;
class Group;
class iMap;


class MainGameManager
{
	SINGLETON(MainGameManager)

	void Init ();
	void Update ();
	void Render ( );
	void WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	void Destroy();

private:

	void SetLight ();

	CameraCtrl  cameraCtrl;
	GridCtrl    gridCtrl;
	CharacterCtrl characterCtrl;
	UIManager	uiManager;
	//LinearInterpolation* lerp;

	std::vector<Group*> groupList;
	std::vector<Group*> groupList2;
	iMap*				mapObject;
	CubeCtrl*			cubeCtrl;
};

