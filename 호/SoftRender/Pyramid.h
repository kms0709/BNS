#pragma once
class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	void Init( D3DXCOLOR c, D3DXMATRIXA16& _world );
	void Render();

private:
	std::vector<VertexPN> vertexList;
	D3DXMATRIXA16 worldMatrix;
	D3DMATERIAL9 material;

	IDirect3DVertexBuffer9* _pcBuffer;
};

