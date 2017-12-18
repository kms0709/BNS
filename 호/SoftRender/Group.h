#pragma once

#include "MatrialTexture.h"

class Group : public Object
{
public:
	Group ();
	~Group ();

	void init();
	void Render ();

protected:

	GETSET_REF ( vector<VertexPNT>, PNTVerts, PNTVerts );
	GETSET_ADD_REF ( MaterialTexture*, materialTexture, MaterialTexture );
};

