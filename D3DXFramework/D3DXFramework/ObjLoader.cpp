#include "stdafx.h"
#include "stdio.h"
#include "ObjLoader.h"


ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::LoadObj( wchar_t* folderPath, wchar_t* filePath, D3DXMATRIX * pmat, OUT vector<Group*>& pgroup )
{
	vector<D3DXVECTOR3> vList;
	vector<D3DXVECTOR3> vnList;
	vector<D3DXVECTOR2> vtList;
	vector<VertexPNT> pntList;

	folderName = folderPath;

	wstring fullpath;
	fullpath = folderName + filePath;

	FILE* pFile = NULL;
	_wfopen_s( &pFile, fullpath.c_str(), L"r" );

	wstring materialName;

	while ( !feof( pFile ) )
	{
		wchar_t buffer[ 1024 ];
		fgetws( buffer, 1024, pFile );

		if ( buffer[ 0 ] == '#' ) // 주석
			continue;
		else if ( buffer[ 0 ] == 'm' ) // mtl파일
		{
			wchar_t mtlPath[ 128 ];
			swscanf( buffer, L"%*s %s", mtlPath );
			wstring mtlFullPath( folderPath );
			mtlFullPath = mtlFullPath + mtlPath;
			LoadMtl( mtlFullPath.c_str() );
		}
		else if ( buffer[ 0 ] == 'g' ) // 그룹
		{
			if ( pntList.empty() )
				continue;
			Group* pGroup = new Group;
			pGroup->SetVertexPNT( pntList );
			pGroup->SetMaterialTexture( TexMaterials[ materialName ] );
			pgroup.push_back( pGroup );
			pntList.clear();
		}
		else if ( buffer[ 0 ] == 'v' ) // 버텍스
		{
			if ( buffer[ 1 ] == 't' )
			{
				float fx, fy;
				swscanf( buffer, L"%*s %f %f %*f", &fx, &fy );
				vtList.push_back( D3DXVECTOR2( fx, fy ) );
			}
			else if ( buffer[ 1 ] == 'n' )
			{
				float fx, fy, fz;
				swscanf( buffer, L"%*s %f %f %f", &fx, &fy, &fz );
				vnList.push_back( D3DXVECTOR3( fx, fy, fz ) );
			}
			else
			{
				float fx, fy, fz;
				swscanf( buffer, L"%*s %f %f %f", &fx, &fy, &fz );
				vList.push_back( D3DXVECTOR3( fx, fy, fz ) );
			}
		}
		else if ( buffer[ 0 ] == 'u' ) // 머테리얼 사용
		{
			wchar_t secondName[ 1024 ];
			swscanf( buffer, L"%*s %s", secondName );
			materialName = secondName;
		}
		else if ( buffer[ 0 ] == 'f' ) // 버텍스 넣기
		{
			int listIndex[ 3 ][ 3 ];
			swscanf( buffer, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&listIndex[ 0 ][ 0 ], &listIndex[ 0 ][ 1 ], &listIndex[ 0 ][ 2 ],
				&listIndex[ 1 ][ 0 ], &listIndex[ 1 ][ 1 ], &listIndex[ 1 ][ 2 ],
				&listIndex[ 2 ][ 0 ], &listIndex[ 2 ][ 1 ], &listIndex[ 2 ][ 2 ] );

			for ( int i = 0; i < 3; ++i )
			{
				VertexPNT tempVets;
				tempVets.p = vList[ listIndex[ i ][ 0 ] - 1 ];
				tempVets.t = vtList[ listIndex[ i ][ 1 ] - 1 ];
				tempVets.n = vnList[ listIndex[ i ][ 2 ] - 1 ];

				if ( pmat )
				{
					D3DXVec3TransformCoord( &tempVets.p, &tempVets.p, pmat );
					D3DXVec3TransformNormal( &tempVets.n, &tempVets.n, pmat );
				}

				pntList.push_back( tempVets );
			}
		}
	}

	for each ( auto it in TexMaterials )
		SAFE_RELEASE( it.second );

	TexMaterials.clear();

	fclose( pFile );
}

void ObjLoader::LoadObjMesh( wchar_t* path, D3DXMATRIX * pmat, OUT LPD3DXMESH & pmesh, OUT vector<MaterialTexture*> & pMTList )
{
	vector<D3DXVECTOR3> vList;
	vector<D3DXVECTOR3> vnList;
	vector<D3DXVECTOR2> vtList;
	vector<VertexPNT> pntList;
	vector<int> aList;
	//	vector<Group*> gList;

	FILE* pFile = NULL;
	_wfopen_s( &pFile, path, L"r" );

	wstring materialName;

	while ( !feof( pFile ) )
	{
		wchar_t buffer[ 1024 ];
		fgetws( buffer, 1024, pFile );

		if ( buffer[ 0 ] == '#' ) // 주석
			continue;
		else if ( buffer[ 0 ] == 'm' ) // mtl파일
		{
			wchar_t mtlPath[ 128 ];
			swscanf( buffer, L"%*s %s", mtlPath );
			LoadMtl( mtlPath );

			pMTList.resize( TexMaterials.size() );
			for each ( auto it in TexMaterials )
			{
				pMTList[ it.second->GetMeshID() ] = it.second;
			}

		}
		//		else if ( buffer[ 0 ] == 'g' ) // 그룹
		//		{
		//			if ( pntList.empty() )
		//				continue;
		//			Group* pGroup = new Group;
		//			pGroup->SetVertexPNT( pntList );
		//			pGroup->SetMaterialTexture( TexMaterials[ materialName ] );
		//			gList.push_back( pGroup );
		//			pntList.clear();
		//		}
		else if ( buffer[ 0 ] == 'v' ) // 버텍스
		{
			if ( buffer[ 1 ] == 't' )
			{
				float fx, fy;
				swscanf( buffer, L"%*s %f %f %*f", &fx, &fy );
				vtList.push_back( D3DXVECTOR2( fx, fy ) );
			}
			else if ( buffer[ 1 ] == 'n' )
			{
				float fx, fy, fz;
				swscanf( buffer, L"%*s %f %f %f", &fx, &fy, &fz );
				vnList.push_back( D3DXVECTOR3( fx, fy, fz ) );
			}
			else
			{
				float fx, fy, fz;
				swscanf( buffer, L"%*s %f %f %f", &fx, &fy, &fz );
				vList.push_back( D3DXVECTOR3( fx, fy, fz ) );
			}
		}
		else if ( buffer[ 0 ] == 'u' ) // 머테리얼 사용
		{
			wchar_t secondName[ 1024 ];
			swscanf( buffer, L"%*s %s", secondName );
			materialName = secondName;
		}
		else if ( buffer[ 0 ] == 'f' ) // 버텍스 넣기
		{
			int listIndex[ 3 ][ 3 ];
			swscanf( buffer, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&listIndex[ 0 ][ 0 ], &listIndex[ 0 ][ 1 ], &listIndex[ 0 ][ 2 ],
				&listIndex[ 1 ][ 0 ], &listIndex[ 1 ][ 1 ], &listIndex[ 1 ][ 2 ],
				&listIndex[ 2 ][ 0 ], &listIndex[ 2 ][ 1 ], &listIndex[ 2 ][ 2 ] );

			for ( int i = 0; i < 3; ++i )
			{
				VertexPNT tempVets;
				tempVets.p = vList[ listIndex[ i ][ 0 ] - 1 ];
				tempVets.t = vtList[ listIndex[ i ][ 1 ] - 1 ];
				tempVets.n = vnList[ listIndex[ i ][ 2 ] - 1 ];

				if ( pmat )
				{
					D3DXVec3TransformCoord( &tempVets.p, &tempVets.p, pmat );
					D3DXVec3TransformNormal( &tempVets.n, &tempVets.n, pmat );
				}

				pntList.push_back( tempVets );
			}
			aList.push_back( TexMaterials[ materialName ]->GetMeshID() );
		}
	}

	//	for each ( auto it in TexMaterials )
	//		SAFE_RELEASE( it.second );
	//	
	//	TexMaterials.clear();

	fclose( pFile );

	D3DXCreateMeshFVF(
		pntList.size() / 3,
		pntList.size(),
		D3DXMESH_MANAGED,
		VertexPNT::FVF,
		D3DDevice,
		&pmesh );

	//	IDirect3DVertexBuffer9* vb = 0;
	//	IDirect3DIndexBuffer9* ib = 0;
	//	pmesh->GetVertexBuffer( &vb );
	//	pmesh->GetIndexBuffer( &ib );


	VertexPNT* p = 0;
	pmesh->LockVertexBuffer( 0, ( void** ) &p );
	for ( int i = 0; i < pntList.size(); ++i )
	{
		p[ i ] = pntList[ i ];
	}
	pmesh->UnlockVertexBuffer();

	WORD* n = 0;
	pmesh->LockIndexBuffer( 0, ( void** ) &n );
	for ( int i = 0; i < pntList.size(); ++i )
	{
		n[ i ] = i;
	}
	pmesh->UnlockIndexBuffer();

	DWORD* b = 0;
	pmesh->LockAttributeBuffer( 0, &b );
	for ( int i = 0; i < aList.size(); ++i )
	{
		b[ i ] = aList[ i ];
	}
	pmesh->UnlockAttributeBuffer();

	vector<DWORD> adjacencyBuffer( pmesh->GetNumFaces() * 3 );
	pmesh->GenerateAdjacency( 0.0f, &adjacencyBuffer[ 0 ] );

	pmesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[ 0 ],
		0, 0, 0 );
}

void ObjLoader::LoadMtl( wstring path )
{
	FILE* pFile = NULL;
	_wfopen_s( &pFile, path.c_str(), L"r" );

	int i = 0;
	wstring mtlName;

	while ( true )
	{
		if ( feof( pFile ) )
			break;

		wchar_t buffer[ 1024 ];
		fgetws( buffer, 1024, pFile );

		if ( buffer[ 0 ] == '#' )
			continue;
		else if ( buffer[ 0 ] == 'n' )
		{
			wchar_t secondName[ 1024 ];
			swscanf( buffer, L"%*s %s", secondName );
			mtlName = secondName;

			SAFE_RELEASE( TexMaterials[ mtlName ] );
			TexMaterials[ mtlName ] = new MaterialTexture();
			//			tm = new MaterialTexture;
		}
		else if ( buffer[ 0 ] == 'K' )
		{
			float x, y, z;
			swscanf( buffer, L"%*s %f %f %f", &x, &y, &z );
			D3DXCOLOR color( x, y, z, 1.0f );
			D3DMATERIAL9& stMtl = TexMaterials[ mtlName ]->GetMaterial();

			if ( buffer[ 1 ] == 'a' )
			{
				stMtl.Ambient = color;
			}
			if ( buffer[ 1 ] == 'd' )
			{
				stMtl.Diffuse = color;
			}
			if ( buffer[ 1 ] == 's' )
			{
				stMtl.Specular = color;
			}
		}
		else if ( buffer[ 0 ] == 'm' )
		{
			wchar_t texName[ 1024 ];
			swscanf( buffer, L"%*s %s", texName );
			wstring fullpath = folderName + texName;

			TexMaterials[ mtlName ]->SetTexture( MANAGER_TEXTURE->GetTexture( fullpath ) );
			TexMaterials[ mtlName ]->SetMeshID( i );
			++i;
		}
	}
	fclose( pFile );
}
