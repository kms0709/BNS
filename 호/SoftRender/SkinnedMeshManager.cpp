#include "stdafx.h"
#include "SkinnedMeshManager.h"

SkinnedMeshManager::SkinnedMeshManager() {}
SkinnedMeshManager::~SkinnedMeshManager() {}


SkinnedMesh* SkinnedMeshManager::GetSkinnedMesh(char* szFolder, char* szFile)
{
	if (skinnedMeshMapList.find(szFile) != skinnedMeshMapList.end())
	{
		return skinnedMeshMapList.find(szFile)->second;
	}

	SkinnedMesh* skinmesh = new SkinnedMesh;

	skinmesh->Load(szFolder, szFile);

	skinnedMeshMapList.insert(make_pair(szFile, skinmesh));

	return skinmesh;
}

void SkinnedMeshManager::Destroy()
{
	for each(auto it in skinnedMeshMapList)
	{
		it.second->Destroy();
	}
}
