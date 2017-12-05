#include "stdafx.h"
#include "SkinnedMeshManager.h"


SkinnedMesh * SkinnedMeshManager::GetSkinnedMesh( wchar_t * szFolder, wchar_t * szFile )
{
	wstring fullPath( szFolder );
	fullPath = fullPath + wstring( L"/" ) + wstring( szFile );

	if ( skinnedMeshMapList.find( fullPath ) == skinnedMeshMapList.end() )
	{
		SkinnedMesh* skinnedMesh = new SkinnedMesh;
		skinnedMesh->Load( szFolder, szFile );

		//		skinnedMeshMapList.insert( pair<wstring, SkinnedMesh*>( fullPath, skinnedMesh ) );
		skinnedMeshMapList[ fullPath ] = skinnedMesh;
	}

	return skinnedMeshMapList[ fullPath ];
}

void SkinnedMeshManager::Destroy()
{
	for each ( auto it in skinnedMeshMapList )
	{
		it.second->Destroy();
	}
	skinnedMeshMapList.clear();
}
