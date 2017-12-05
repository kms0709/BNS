#include "stdafx.h"
#include "DirectXDevice.h"


DirectXDevice::DirectXDevice()
	: _d3d9( NULL )
	, _d3dDevice( NULL )
{
}


DirectXDevice::~DirectXDevice()
{
}

HRESULT DirectXDevice::Init()
{
	if ( ( _d3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
	{
		::MessageBox( 0, L"D3D_SDK_VERSION 불러오기 실패!", 0, 0 );
		return E_FAIL;
	}

	D3DCAPS9 caps;
	_d3d9->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	int vp = 0;
	if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if ( FAILED( _d3d9->CreateDevice( 
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		g_hWnd, 
		vp, 
		&d3dpp, 
		&_d3dDevice ) ) )
	{
		::MessageBox( 0, L"CreateDevice 실패!", 0, 0 );
		return E_FAIL;
	}

	return S_OK;
}

void DirectXDevice::Release()
{
	if ( _d3d9 != NULL )
		_d3d9->Release();

	if ( _d3dDevice != NULL )
	{
		ULONG ul = _d3dDevice->Release();
		assert( ul == 0 && "unreleased object..." );
	}
}


