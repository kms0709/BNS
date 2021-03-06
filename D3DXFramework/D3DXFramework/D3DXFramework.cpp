// D3DXFramework.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "D3DXFramework.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
//WCHAR szTitle[ MAX_LOADSTRING ];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[ MAX_LOADSTRING ];            // 기본 창 클래스 이름입니다.

HWND g_hWnd;
MainGame* _mainGame = nullptr;

POINT g_ptMouse;				// 마우스 좌표
BOOL g_LButton = false;			// 마우스 좌클릭
BOOL g_RButton = false;			// 마우스 우클릭

RECT g_ClientRC;				// 윈도우 창 크기
RECT g_WindowRC;				// 윈도우 위치

BOOL g_WindowActive = false;	// 윈도우 활성화 상태
BOOL g_cursorActive = false;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass( HINSTANCE hInstance );
BOOL                InitInstance( HINSTANCE, int );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK    About( HWND, UINT, WPARAM, LPARAM );

void setWindowsSize( int x, int y, int width, int height );

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
//	LoadStringW( hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING );
	LoadStringW( hInstance, IDC_D3DXFRAMEWORK, szWindowClass, MAX_LOADSTRING );
	MyRegisterClass( hInstance );

	// 응용 프로그램 초기화를 수행합니다.
	if ( !InitInstance( hInstance, nCmdShow ) )
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDC_D3DXFRAMEWORK ) );

	_mainGame = new MainGame;
	// 메인게임이 초기화 안되면 종료
	if ( FAILED( _mainGame->Init() ) )
	{
		return 0;
	}

	MSG msg;

	// 기본 메시지 루프입니다.
	while ( true )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT ) break;
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			_mainGame->Update();

			MANAGER_DX->BeginDraw();
			_mainGame->Render();
			MANAGER_DX->EndDraw();

//			AUTORELEASE->Drain();
		}

	}

	// 메세지 루프를 다 돌으면 해제
	_mainGame->Release();

	return ( int ) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass( HINSTANCE hInstance )
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_D3DXFRAMEWORK ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = MAKEINTRESOURCEW( IDC_D3DXFRAMEWORK );
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	return RegisterClassExW( &wcex );
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	// 윈도우를 만들어줍니다.
	g_hWnd = CreateWindow( 
		szWindowClass, 
		WINNAME,
		WINSTYLE,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		nullptr, 
		nullptr,
		hInstance, 
		nullptr
	);

	if ( !g_hWnd )
	{
		return FALSE;
	}

	// 윈도우 창을 보여줍니다.
	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	return _mainGame->MainProc( hWnd, message, wParam, lParam );

// 이전 메세지 스위치
//	switch ( message )
//	{
//	case WM_COMMAND:
//		{
//			int wmId = LOWORD( wParam );
//			// 메뉴 선택을 구문 분석합니다.
//			switch ( wmId )
//			{
//			case IDM_ABOUT:
//				DialogBox( _hInst, MAKEINTRESOURCE( IDD_ABOUTBOX ), hWnd, About );
//				break;
//			case IDM_EXIT:
//				DestroyWindow( hWnd );
//				break;
//			default:
//				return DefWindowProc( hWnd, message, wParam, lParam );
//			}
//		}
//		break;
//	case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//			HDC hdc = BeginPaint( hWnd, &ps );
//			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
//			EndPaint( hWnd, &ps );
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage( 0 );
//		break;
//	default:
//		return DefWindowProc( hWnd, message, wParam, lParam );
//	}
//	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER( lParam );
	switch ( message )
	{
	case WM_INITDIALOG:
		return ( INT_PTR ) TRUE;

	case WM_COMMAND:
		if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
		{
			EndDialog( hDlg, LOWORD( wParam ) );
			return ( INT_PTR ) TRUE;
		}
		break;
	}
	return ( INT_PTR ) FALSE;
}

//클라이언트 영역 재조정 함수
void setWindowsSize( int x, int y, int width, int height )
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;		//가로크기
	winRect.bottom = height;	//세로크기

	AdjustWindowRect( &winRect, WINSTYLE, false );

	SetWindowPos( g_hWnd, NULL, x, y, ( winRect.right - winRect.left ),
		( winRect.bottom - winRect.top ), SWP_NOZORDER | SWP_NOMOVE );

}