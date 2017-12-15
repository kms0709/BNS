#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
	: fDistance( 0 )
	, eye( 0, 0, 0 )
	, lookAt( 0, 0, 0 )
	, up( 0, 0, 0 )
	, fRotX( 0.0f )
	, fRotY( 0.0f )
{
	ZeroMemory( &viewMatrix, sizeof( D3DXMATRIX ) );
	ZeroMemory( &projMatrix, sizeof( D3DXMATRIX ) );
}


CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
	fRotX = 0.0f;
	fRotY = 0.0f;

	fDistance = 100.0f;

	eye = D3DXVECTOR3( 0.0f, 0.0f, -fDistance );
	lookAt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	prevPtMouse = { 0, 0 };

	D3DXMatrixLookAtLH( &viewMatrix, &eye, &lookAt, &up );
	D3DDevice->SetTransform( D3DTS_VIEW, &viewMatrix );

	D3DXMatrixPerspectiveFovLH( 
		&projMatrix, 
		D3DX_PI * 0.25f, 
		( float ) g_ClientRC.right / ( float ) g_ClientRC.bottom,
		1, 
		1000 
	);
	D3DDevice->SetTransform( D3DTS_PROJECTION, &projMatrix );

}

void CameraManager::Release()
{
}

void CameraManager::Update()
{
	eye = D3DXVECTOR3( 0, 0, -fDistance );

	D3DXMATRIX matRotX, matRotY, matRot;

	D3DXMatrixRotationX( &matRotX, fRotX );
	D3DXMatrixRotationY( &matRotY, fRotY );

	matRot = matRotX * matRotY;
	D3DXVec3TransformCoord( &eye, &eye, &matRot );

	D3DXVECTOR3 currentLookAt = lookAt;
	currentLookAt.y = lookAt.y + 30;
	eye = currentLookAt + eye;

	D3DXMatrixLookAtLH( &viewMatrix, &eye, &currentLookAt, &up );
	D3DDevice->SetTransform( D3DTS_VIEW, &viewMatrix );

	if ( MANAGER_INPUT->IsKey( SPKL_RALT ) )
	{
		if ( g_cursorActive )
		{
			SetCursorPos( centerPos.x, centerPos.y );
			g_cursorActive = false;
		}
		else
		{
			g_cursorActive = true;
		}
	}
}

void CameraManager::Render()
{
}

void CameraManager::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	case WM_MOUSEMOVE:
		{
//			if ( !g_cursorActive )
//			{
				RECT currentWindowRC;
				POINT currentDistance;

				currentDistance.x = ( g_WindowRC.right - ( g_WindowRC.left + g_ClientRC.right ) ) / 2;
				currentDistance.y = ( g_WindowRC.bottom - ( g_WindowRC.top + g_ClientRC.bottom ) ) / 2;

				currentWindowRC.left = g_WindowRC.left + currentDistance.x;
				currentWindowRC.right = g_WindowRC.right - currentDistance.x;
				currentWindowRC.top = g_WindowRC.top + currentDistance.x;
				currentWindowRC.bottom = g_WindowRC.bottom - currentDistance.x;

				centerPos.x = currentWindowRC.left + ( currentWindowRC.right - currentWindowRC.left ) / 2;
				centerPos.y = currentWindowRC.top + ( currentWindowRC.bottom - currentWindowRC.top ) / 2;

				//			prevPtMouse = centerPos;
				GetCursorPos( &prevPtMouse );

				fRotY += ( prevPtMouse.x - centerPos.x ) / 500.0f;
				fRotX += ( prevPtMouse.y - centerPos.y ) / 500.0f;

				if ( fRotX <= -D3DX_PI * 0.5f - EPSILON )
				{
					fRotX = -D3DX_PI * 0.5f + EPSILON;
				}

				if ( fRotX >= D3DX_PI * 0.5f + EPSILON )
				{
					fRotX = D3DX_PI * 0.5f - EPSILON;
				}

				SetCursorPos( centerPos.x, centerPos.y );
//			}

//			if ( centerPos.x != g_ptMouse.x || centerPos.y != g_ptMouse.y )
//			{
//				fRotY += ( g_ptMouse.x - centerPos.x ) / 100.0f;
//				fRotX += ( g_ptMouse.y - centerPos.y ) / 100.0f;
//
//				if ( fRotX <= -D3DX_PI * 0.5f - EPSILON )
//				{
//					fRotX = -D3DX_PI * 0.5f + EPSILON;
//				}
//
//				if ( fRotX >= D3DX_PI * 0.5f + EPSILON )
//				{
//					fRotX = D3DX_PI * 0.5f - EPSILON;
//				}
//
//
//				SetCursorPos( centerPos.x, centerPos.y );
//				prevPtMouse = g_ptMouse;
//			}
			
//			g_ptMouse = prevPtMouse;

//			if ( g_LButton )
//			{
//				fRotY += ( g_ptMouse.x - prevPtMouse.x ) / 100.0f;
//				fRotX += ( g_ptMouse.y - prevPtMouse.y ) / 100.0f;
//
//				if ( fRotX <= -D3DX_PI * 0.5f - EPSILON )
//				{
//					fRotX = -D3DX_PI * 0.5f + EPSILON;
//				}
//
//				if ( fRotX >= D3DX_PI * 0.5f + EPSILON )
//				{
//					fRotX = D3DX_PI * 0.5f - EPSILON;
//				}
//
//				prevPtMouse = g_ptMouse;
//			}
//			else
//			{
//				prevPtMouse = g_ptMouse;
//			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			if ( fDistance < 2.0f )
				fDistance = 2.0f;
			fDistance -= GET_WHEEL_DELTA_WPARAM( wParam ) / 50.0f;
		}
		break;
	}
}


