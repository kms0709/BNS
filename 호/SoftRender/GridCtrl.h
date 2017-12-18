#pragma once
class GridCtrl
{
public:
	GridCtrl ();
	~GridCtrl ();

	void Init ();	
	void Render ();


private:
	vector<VertexPC> vertexList;
	vector<Pyramid*> pyramidList;

	IDirect3DVertexBuffer9* _pcBuffer;
};

