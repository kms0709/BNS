
#pragma once


class MaterialTexture;
class Group;

class OBJLoader : public Object
{
public:
	OBJLoader ();
	~OBJLoader ();
	

	void SetPath (char* path); 
	void Load ( IN char* filename,
		IN D3DXMATRIXA16* pmat,
		OUT std::vector<Group*>& vecGroup );

	LPD3DXMESH meshLoad(IN char* filename,
		IN D3DXMATRIXA16* pmat,
		OUT vector<MaterialTexture*>& mtList);

protected:
	void LoadMtlLib ( char* szFullPath );

protected:
	std::map<std::string, MaterialTexture*>  mapMaterialTexture;
	std::string path;

};

