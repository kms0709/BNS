#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::Init( void )
{
	_managerInit = false;

	return S_OK;
}

HRESULT GameNode::Init( bool managerInit )
{
	_managerInit = managerInit;

	GetClientRect( g_hWnd, &g_ClientRC );

	if ( _managerInit )
	{
		MANAGER_DX->Init();
		MANAGER_INPUT->Init( DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY );
		MANAGER_SCENE->Init();
		MANAGER_SOUND->Init();
		MANAGER_TEXTURE->Init();
		MANAGER_TIME->Init();

		MANAGER_CAMERA->Init();

	}

	return S_OK;
}

void GameNode::Release( void )
{
	if ( _managerInit )
	{
		MANAGER_SCENE->Release();
		MANAGER_CAMERA->Release();

		MANAGER_INPUT->FreeDirectInput();

		MANAGER_FONT->Destroy();
		MANAGER_OBJECT->Destroy();
		MANAGER_SKINNED->Destroy();

		MANAGER_TEXTURE->Release();
		MANAGER_DX->Release();
		MANAGER_TIME->Release();
		MANAGER_SOUND->Release();

		

		MANAGER_CAMERA->ReleaseSingleton();
		MANAGER_FONT->ReleaseSingleton();
		MANAGER_INPUT->ReleaseSingleton();
		MANAGER_OBJECT->ReleaseSingleton();
		MANAGER_SKINNED->ReleaseSingleton();
		MANAGER_SOUND->ReleaseSingleton();
		MANAGER_SCENE->ReleaseSingleton();
		MANAGER_DX->ReleaseSingleton();
		MANAGER_TIME->ReleaseSingleton();
	}
}

void GameNode::Update( void )
{
	MANAGER_CAMERA->Update();
	MANAGER_INPUT->Update();
	MANAGER_TIME->Update();
	MANAGER_SOUND->Update();

	GetClientRect( g_hWnd, &g_ClientRC );
	GetWindowRect( g_hWnd, &g_WindowRC );

	//RECT currentWindowRC;
	//POINT currentDistance;

	//currentDistance.x = (g_WindowRC.right - ( g_WindowRC.left + g_ClientRC.right ) ) / 2;
	//currentDistance.y = (g_WindowRC.bottom - ( g_WindowRC.top + g_ClientRC.bottom ) ) / 2;

	//currentWindowRC.left = g_WindowRC.left + currentDistance.x;
	//currentWindowRC.right = g_WindowRC.right - currentDistance.x;
	//currentWindowRC.top = g_WindowRC.top + currentDistance.x;
	//currentWindowRC.bottom = g_WindowRC.bottom - currentDistance.x;

//	if ( g_WindowActive )
//		ClipCursor( &currentWindowRC );

	//POINT centerPos;
	//centerPos.x = currentWindowRC.left + ( currentWindowRC.right - currentWindowRC.left ) / 2;
	//centerPos.y = currentWindowRC.top + ( currentWindowRC.bottom - currentWindowRC.top ) / 2;

//	SetCursorPos( centerPos.x, centerPos.y );

}

void GameNode::Render( void )
{
}

LRESULT GameNode::MainProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	MANAGER_INPUT->WndProc( message, wParam, lParam );
	MANAGER_CAMERA->WndProc( hWnd, message, wParam, lParam );

	switch ( message )
	{
	case WM_SETCURSOR:
		{
//			if ( g_cursorActive )
//			{
////				SetCursor( LoadCursor( nullptr, IDC_ARROW ) );
//				ShowCursor( TRUE );
//				return true;
//			}
//			else
//			{
////				SetCursor( NULL );
//				ShowCursor( FALSE );
//				return true;
//			}
			ShowCursor( FALSE );
			return true;
		}
		break;
	case WM_ACTIVATEAPP:
			g_WindowActive = wParam;

		break;
		//마우스 좌표를 읽어오는 함수
	case WM_MOUSEMOVE:
		g_ptMouse.x = static_cast< float >LOWORD( lParam );
		g_ptMouse.y = static_cast< float >HIWORD( lParam );
		break;

	case WM_KEYDOWN:
		switch ( wParam )
		{
		case VK_ESCAPE:
			PostMessage( hWnd, WM_DESTROY, 0, 0 );
			break;

		}
		break;

	case WM_LBUTTONDOWN:
		g_LButton = true;
		break;

	case WM_LBUTTONUP:
		g_LButton = false;
		break;

	case WM_RBUTTONDOWN:
		g_RButton = true;
		break;

	case WM_RBUTTONUP:
		g_RButton = false;
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return ( DefWindowProc( hWnd, message, wParam, lParam ) );
}
