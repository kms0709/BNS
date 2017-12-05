#include "stdafx.h"
#include "DirectXManager.h"


DirectXManager::DirectXManager()
{
}


DirectXManager::~DirectXManager()
{
}

void DirectXManager::Init()
{
	D3DXDevice = new DirectXDevice;
	D3DXDevice->Init();
}

void DirectXManager::Release()
{
	SAFE_RELEASE( D3DXDevice );
}

void DirectXManager::BeginDraw()
{
	D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 55, 55, 55 ), 1.0f, 0 );
	D3DDevice->BeginScene();
}

void DirectXManager::EndDraw()
{
	D3DDevice->EndScene();
	D3DDevice->Present( NULL, NULL, NULL, NULL );
}


