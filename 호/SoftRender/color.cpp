#include "stdafx.h"
#include "color.h"


color::color()
{
}


color::~color()
{
	SAFE_RELEASE(_spherMesh);
	SAFE_RELEASE(_effect);
}

void color::init()
{
	D3DXCreateSphere(D3DDevice, 1.0f, 10, 10, &_spherMesh, nullptr);

	D3DXMatrixTranslation(&_matWorld, 0.0f, 5.0f, 0.0f);

	_effect = loadEffect("green.fx");
}

void color::render()
{
	_effect->SetMatrix("matWorld", &_matWorld);
	_effect->SetMatrix("matView", _pMatView);
	_effect->SetMatrix("matProjection", _pMatProjec);

	UINT uiPasses = 0, uiPass;

	// run through each pass and draw
	_effect->Begin(&uiPasses, 0);
	for (uiPass = 0; uiPass < uiPasses; ++uiPass)
	{
		_effect->BeginPass(uiPass);

		{
			_spherMesh->DrawSubset(0);
		}

		_effect->EndPass();
	}
	_effect->End();
}

void color::update()
{
}

LPD3DXEFFECT color::loadEffect(char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	HRESULT hr;
	if (FAILED(hr = D3DXCreateEffectFromFileA(D3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

