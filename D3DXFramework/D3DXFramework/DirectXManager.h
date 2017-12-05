#pragma once
#include "SingletonBase.h"
#include "DirectXDevice.h"

class DirectXManager : public SingletonBase<DirectXManager>
{
private:
	DirectXDevice* D3DXDevice;

public:
	void Init();
	void Release();

	void BeginDraw();	// 그리기 시작 - MainGame에 Render() 안에 들어감
	void EndDraw();		// 그리기 끝 - MainGame에 Render() 안에 들어감

	LPDIRECT3DDEVICE9 GetDevice() { return D3DXDevice->GetDevice(); }

	DirectXManager();
	~DirectXManager();
};

