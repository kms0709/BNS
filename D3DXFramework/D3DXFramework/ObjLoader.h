#pragma once

class MaterialTexture;
class Group;

class ObjLoader
{
private:
	map<wstring, MaterialTexture*> TexMaterials;
	wstring folderName;

protected:
	void LoadMtl( wstring path );

public:
	ObjLoader();
	~ObjLoader();

	void LoadObj( wchar_t* folderPath, wchar_t* filePath, D3DXMATRIX* pmat, OUT vector<Group*>& pgroup );
	void LoadObjMesh( wchar_t* path, D3DXMATRIX * pmat, OUT LPD3DXMESH & pmesh, OUT vector<MaterialTexture*> & pMTList );

};

