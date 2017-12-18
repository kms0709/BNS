// SoftRender.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SoftRender.h"

#define MAX_LOADSTRING 1000

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

LPCWSTR _winName = TEXT("3DGame");


const int TIMER_ID = 654;
HWND g_hWnd;
HDC _hwnd;

POINT _ptMouse;
//MainGameManager* g_pMainGameManager;


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOFTRENDER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOFTRENDER));	


	srand(GetTickCount());
	//g_pMainGameManager = new MainGameManager ();
	VideoDevice::GetInstance()->Init();
	MainGameManager::GetInstance()->Init ();

	SetTimer ( g_hWnd, TIMER_ID, 10, NULL );

    MSG msg;
    // �⺻ �޽��� �����Դϴ�.
	while ( true )
	{
		if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) ) {
			if ( msg.message == WM_QUIT ) {
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

		}
		else
		{
			MainGameManager::GetInstance()->Update();
			VideoDevice::GetInstance()->RenderBegin();


			MainGameManager::GetInstance()->Render();
			VideoDevice::GetInstance()->RenderEnd();

			g_pAutoReleasePool->Drain();

		}
	}
	MainGameManager::GetInstance()->Destroy();

	KillTimer ( g_hWnd, TIMER_ID );

	//delete g_pMainGameManager;

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MYICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOFTRENDER);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDC_MYICON));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass,	// ??
	   _winName,							// ���� ��µȴ� �̸�
	   WS_OVERLAPPEDWINDOW,					// ���â ��Ÿ��
       CW_USEDEFAULT,						// �ܼ�â ���� ��ǥ X
	   0,									// Y
	   WINSIZEX,							// ���� ����
	   WINSIZEY,							// ����
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//if( g_pMainGameManager )
	//	g_pMainGameManager->WndProc ( hWnd, message, wParam, lParam );
	MainGameManager::GetInstance()->WndProc( hWnd, message, wParam, lParam );

    switch (message)
    {
	//case WM_TIMER:
	//	{
	//		if ( g_pMainGameManager != nullptr ) {
	//			g_pMainGameManager->Update ();
	//		}
	//		InvalidateRect ( g_hWnd, NULL, false );
	//	}
	//	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_MOUSEMOVE:
		// ���콺 ��ġ ����
		_ptMouse.x = static_cast<float> LOWORD(lParam);
		_ptMouse.y = static_cast<float> HIWORD(lParam);


		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
			// esc ������ ������
		case VK_ESCAPE:
			PostMessage(g_hWnd, WM_DESTROY, wParam, lParam);
			break;
		default:
			break;
		}

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			_hwnd = hdc;
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			//if ( g_pMainGameManager != nullptr ) {
			//	g_pMainGameManager->Render ( hdc );
			//}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
