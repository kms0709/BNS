#pragma once

class MaterialTexture;

class Group : public Object
{
private:

	GETSET_REF( vector<VertexPNT>, vertexPNT, VertexPNT );
	GETSET_ADD_REF( MaterialTexture*, materialTexture, MaterialTexture );

public:
	Group();
	~Group();

	void Render();
};

