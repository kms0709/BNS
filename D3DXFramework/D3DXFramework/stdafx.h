// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include "targetver.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "imm32.lib")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>


// std::
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

// DirectX 헤더 파일입니다.
#include <d3d9.h>
#include <d3dx9math.h>

#include <initguid.h>
#include <dinput.h>
#include "InputDef.h"
#include "Utility.h"


using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Object.h"
#include "MaterialTexture.h"
#include "Group.h"

#include "AutoReleasePool.h"

#include "CameraManager.h"
#include "DirectXManager.h"
#include "FontManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "SkinnedMeshManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TimeManager.h"


//==================================
// ## 디파인문 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("D3DX Farmework"))
#define WINSTARTX 100			//윈도우 창 시작지점 X좌표
#define WINSTARTY 100			//윈도우 창 시작지점 Y좌표
#define WINSIZEX  1280			//윈도우 창 가로크기
#define WINSIZEY  720			//윈도우 창 세로크기
#define WINSTYLE  WS_CAPTION


#define MANAGER_CAMERA	CameraManager::GetSingleton()
#define MANAGER_DX		DirectXManager::GetSingleton()
#define MANAGER_FONT	FontManager::GetSingleton()
#define MANAGER_INPUT	InputManager::GetSingleton()
#define MANAGER_OBJECT	ObjectManager::GetSingleton()
#define MANAGER_SCENE	SceneManager::GetSingleton()
#define MANAGER_SKINNED SkinnedMeshManager::GetSingleton()
#define MANAGER_SOUND	SoundManager::GetSingleton()
#define MANAGER_TEXTURE	TextureManager::GetSingleton()
#define MANAGER_TIME	TimeManager::GetSingleton()


#define D3DDevice		MANAGER_DX->GetDevice()
#define AUTORELEASE		AutoReleasePool::GetSingleton()

//==================================
// ## 전역 변수 ##
//==================================

extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;
extern POINT		g_ptMouse;
extern BOOL			g_LButton;
extern BOOL			g_RButton;
extern RECT			g_ClientRC;
extern RECT			g_WindowRC;
extern BOOL			g_WindowActive;
extern BOOL			g_cursorActive;

const float EPSILON = 0.0001f;

//==================================
// ## 메모리 누수 체크 ##
//==================================

#ifndef _MEMORYLEAK_H_
#define _MEMORYLEAK_H_

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
static class MemoryMng
{
public:
	MemoryMng()
	{
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//_CrtSetBreakAlloc(3333);

		//만약 누수 경로가 명확히 뜨지 않을 경우 위의 주석된 줄을 활성화 후
		//누수 경고가 뜬 문장에 제시된 숫자를 괄호안에 넣고 디버깅하면 누수된 줄에 디버깅이 멈춘다
	}
	~MemoryMng()
	{
		_ASSERTE( _CrtCheckMemory() );
	}


} MemoryLeak;
#endif      // _DEBUG
#endif      // _MEMORYLEAK_H_