#pragma once
#include "SingletonBase.h"

#define DIKS_SIZE 256

class InputManager : public SingletonBase<InputManager>
{
public:

	HRESULT Init( DWORD dwCoopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	void FreeDirectInput();

	void Update();


	bool WndProc( UINT message, WPARAM wParam, LPARAM lParam );


	void SetKeyTable();
	HRESULT ReadImmediateData();

	bool IsKey( int KeyCode, BYTE* pEvent = NULL );


	// 현재 눌려있는 키를 검색하여 puiVirKeyCode에 할당한다.
	bool ConvertProcessKey( unsigned int* puiVirKeyCode );

	//VK_SHIFT, VK_CONTROL, VK_MENU, VK_LWIN ,VK_RWIN, VK_TAB 가 눌려있는 상태를 업데이트한다.		
	void UpdateControlKeyState();

	bool GetKeyState( int iSPKLCode ) { return m_bKeyStates[ m_dwVKTable[ iSPKLCode ] ]; }

	LPCSTR GetStateLog() { return m_strNewText.c_str(); }


	string&  GetKeyLog() { return m_strNewText; }


	// 키 입력 테스트용
	void LogRender();

	InputManager();
	~InputManager();

protected:

	BYTE	m_DIKS[ DIKS_SIZE ];
	BYTE	m_DIKSOld[ DIKS_SIZE ];
	BYTE	m_DIKSState[ DIKS_SIZE ];

	bool	m_bKeyStates[ DIKS_SIZE ];
	bool	m_bKeyStatesOld[ DIKS_SIZE ];

	DWORD	m_dwDIKSTable[ DIKS_SIZE ];
	DWORD	m_dwVKTable[ DIKS_SIZE ];

	HWND	m_hWndMainWindow;

	LPDIRECTINPUT8       m_pDI;			// The DirectInput object
	LPDIRECTINPUTDEVICE8 m_pKeyboard;	// The keyboard device 

										// Debug Log
	string		m_strNewText;

	// 키 입력 테스트용
	LPD3DXFONT keyTestFont;
	DWORD textFormat = DT_LEFT | DT_TOP | DT_NOCLIP;
	DWORD color = D3DCOLOR_XRGB( 255, 255, 255 );

public:
	BYTE	keyStateLeft;
	BYTE	keyStateBackSpace;

};

