#pragma once

class CharacterCtrl
{
private:

	D3DXMATRIX matWorld;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	D3DXMATRIX &GetMatrix() { return matWorld; }
	
	CharacterCtrl();
	~CharacterCtrl();
};

