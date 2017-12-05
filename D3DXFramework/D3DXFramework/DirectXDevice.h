#pragma once
class DirectXDevice
{
private:
	LPDIRECT3D9 _d3d9;
	LPDIRECT3DDEVICE9 _d3dDevice;

public:
	HRESULT Init();
	void Release();

	LPDIRECT3DDEVICE9 GetDevice() { return _d3dDevice; }

	DirectXDevice();
	~DirectXDevice();
};

