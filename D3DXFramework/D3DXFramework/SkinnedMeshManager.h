#pragma once
#include "SingletonBase.h"
#include "SkinnedMesh.h"

class SkinnedMeshManager : public SingletonBase<SkinnedMeshManager>
{
private:
	map<wstring, SkinnedMesh*> skinnedMeshMapList;

public:
	SkinnedMesh* GetSkinnedMesh( wchar_t* szFolder, wchar_t* szFile );
	void Destroy();
};

