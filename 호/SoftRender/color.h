#pragma once
class color
{
public:
	color();
	~color();

	void init();
	void render();
	void update();

	LPD3DXEFFECT loadEffect(char*);

	void setViewPtr(D3DXMATRIX* pMat) { _pMatView = pMat; }
	void setProjec(D3DXMATRIX* pMatPro) { _pMatProjec = pMatPro; }

private:
	D3DXMATRIX _matWorld;
	D3DXMATRIX* _pMatView;
	D3DXMATRIX* _pMatProjec;
	LPD3DXMESH _spherMesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

};

