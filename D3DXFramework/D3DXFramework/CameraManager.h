#pragma once
#include "SingletonBase.h"

class CameraManager : public SingletonBase<CameraManager>
{
private:

	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 up;

	float fDistance; 
	float fRotX;
	float fRotY;

	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	POINT prevPtMouse;
	POINT centerPos;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	void WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	float GetfRotY() { return fRotY; }
	void SetTarget( D3DXVECTOR3 t ) { lookAt = t; }

	CameraManager();
	~CameraManager();
};

