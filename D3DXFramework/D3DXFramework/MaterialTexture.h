#pragma once


class MaterialTexture : public Object
{
private:
	GETSET( int, meshID, MeshID ); // �޽� �����
	GETSET_REF( D3DMATERIAL9, material, Material );
	GETSET_ADD_REF( LPDIRECT3DTEXTURE9, texture, Texture );

public:
	MaterialTexture();
	~MaterialTexture();
};

