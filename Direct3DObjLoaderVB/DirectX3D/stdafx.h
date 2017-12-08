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
#include <list>
#include <map>
#include <set>
#include <string>
#include <assert.h>
#include <d3d9.h>
#include <d3dx9math.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



extern HWND g_hWnd;

#include "Utility.h"

#include "Object.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "AutoReleasePool.h"
#include "TimeManager.h"

#include "VideoDevice.h"
#include "TextureManager.h"
#include "FontManager.h"



#include "UIObject.h"
#include "UIImageView.h"
#include "UITextView.h"
#include "UIButton.h"
#include "UIManager.h"

#include "CubeCtrl.h"
#include "CameraCtrl.h"
#include "GridCtrl.h"
#include "CharacterCtrl.h"
#include "LinearInterpolation.h"

#include "MainGameManager.h"





