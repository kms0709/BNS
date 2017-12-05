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

	void BeginDraw();	// �׸��� ���� - MainGame�� Render() �ȿ� ��
	void EndDraw();		// �׸��� �� - MainGame�� Render() �ȿ� ��

	LPDIRECT3DDEVICE9 GetDevice() { return D3DXDevice->GetDevice(); }

	DirectXManager();
	~DirectXManager();
};

