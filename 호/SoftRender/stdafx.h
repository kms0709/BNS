// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

	
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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

// 삼중 포인트
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