#pragma once
class CameraCtrl
{
public:
	CameraCtrl ();
	~CameraCtrl ();

	void Init ();
	void Update ( D3DXVECTOR3 target );
	void WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

	D3DXMATRIXA16 getMatRotaX() { return matRotaionX; }
	D3DXMATRIXA16 getMatRotaY() { return matRotaionY; }
	

	D3DXMATRIX& GetViewMatrix() { return viewMatrix; }
	D3DXMATRIX& GetProjectionMatrix() { return projMatrix; }
	//D3DXMATRIX& GetViewProjectionMatrix ();
	
private:
	D3DXVECTOR3 eyeVector;
	D3DXVECTOR3 lookAtVector;
	D3DXVECTOR3 upVector;

	//Matrix viewMatrix;
	//Matrix projMatrix;

	D3DXMATRIXA16 viewMatrix;
	D3DXMATRIXA16 projMatrix;

	D3DXMATRIXA16 matRotaionX, matRotaionY;


	float fDistance;
	float fRotX;
	float fRotY;


	POINT PrevMousePos;
	bool  isLButtonDown;

};

