#pragma once
class cubeMan
{
private:
	Cube _cube;

	LPDIRECT3DTEXTURE9 _text;

public:
	cubeMan();
	~cubeMan();

	void init(void);
	void update(D3DXMATRIXA16& parentWorldMatrix);
	void render();

	void SetTextureVertex(vector<D3DXVECTOR2>& UVList, vector<D3DXVECTOR2> UVIndex);

	D3DXVECTOR3 getPosition() { return _cube.GetPosition(); }
};

