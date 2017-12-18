#pragma once
#include "SkinnedMesh.h"

#define g_pSkinnedMeshManager SkinnedMeshManager::GetInstance()

class SkinnedMeshManager
{
	SINGLETON(SkinnedMeshManager);

public:
	SkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFile);
	void Destroy ();


private:
	map<string, SkinnedMesh*> skinnedMeshMapList;

};

