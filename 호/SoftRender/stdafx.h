// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

	
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <vector>
#include <d3d9.h>
#include <d3dx9math.h>
#include <assert.h>
#include <map>
#include <list>
#include <string>
#include <set>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define WINSIZEX 1200
#define WINSIZEY 900

#define SINGLETON( className ) private: \
className (); \
~className (); \
public: \
	static className* GetInstance () \
	{ \
		static className instance; \
		return &instance; \
	}

using namespace std;

// ���� ����Ʈ
struct tagThreePoint
{
	tagThreePoint(float _x, float _y, float _z) 
	{ 
		x = _x; 
		y = _y;
		z = _z;
	}

	float x, y, z;
};
//#include "Matrix.h"
//#include "D3DXVECTOR3.h"

#include "Utility.h"

#include "TimeManager.h"
#include "Asciitok.h"

#include "VideoDevice.h"

#include "OBJMap.h"

#include "Cube.h"
#include "Pyramid.h"
#include "GridCtrl.h"
#include "CameraCtrl.h"
#include "CharacterCtrl.h"
#include "cubeMan.h"
#include "AutoReleasePool.h"
#include "uiObj.h"
#include "uiImageView.h"
#include "uiTextView.h"
#include "uiButton.h"
#include "OBJLoader.h"

#include "Group.h"

#include "SkinnedMeshManager.h"
#include "FrustumCulling.h"


#include "Object.h"

#include "ASECharacter.h"
#include "GameObject.h"
#include "ObjectManager.h"

#include "LinearInterpolation.h"


#include "UIManager.h"



#include "textManager.h"
#include "MainGameManager.h"


extern HWND g_hWnd;
extern POINT _ptMouse;
extern HDC _hwnd;

const float EPSILON = 0.0001f;
const float PI = 3.141592f;

const float PI2 = PI * 2;

#ifdef _DEBUG
#pragma comment(linker , "/entry:wWinMainCRTStartup /subsystem:console")
#endif