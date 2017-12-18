#include "stdafx.h"
#include "OBJLoader.h"

#include "MatrialTexture.h"
#include "Group.h"

OBJLoader::OBJLoader ()
{
}


OBJLoader::~OBJLoader ()
{
}

void OBJLoader::SetPath ( char * path )
{
}

void OBJLoader::Load ( IN char * filename, IN D3DXMATRIXA16 * pmat, OUT std::vector<Group*>& groupList )
{
	vector<D3DXVECTOR3> VList;
	vector<D3DXVECTOR2> VTList;
	vector<D3DXVECTOR3> VNList;
	vector<VertexPNT> PNTList;

	string materialName;

	FILE* fp = NULL;

	if ( path.empty() )
		fopen_s ( &fp, filename, "r" );		
	else {
		string fullPath;
		fullPath = path + filename;
		fopen_s ( &fp, fullPath.c_str(), "r" );
	}
		

	while ( true )
	{
		if ( feof ( fp ) )
			break;

		char szTemp[1024];

		fgets ( szTemp, 1024, fp );

		if ( szTemp[0] == '#' )
		{
			continue;
		}
		else if ( szTemp[0] == 'm' )
		{
			char szMtlPath[1024];
			sscanf ( szTemp, "%*s %s", szMtlPath );
			LoadMtlLib ( szMtlPath );
		}
		else if ( szTemp[0] == 'g' )
		{
			if (PNTList.empty()) continue;
			Group* pGroup = new Group();
			pGroup->SetPNTVerts(PNTList);
			pGroup->SetMaterialTexture(mapMaterialTexture[materialName]);
			groupList.push_back(pGroup);
			PNTList.clear();
		}
		else if ( szTemp[0] == 'v' )
		{
			if ( szTemp[1] == 't' )
			{
				float u, v;
				sscanf(szTemp, "%*s %f %f %*f", &u, &v);
				VTList.push_back(D3DXVECTOR2(u, v));
			}
			else if ( szTemp[1] == 'n' )
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				VNList.push_back(D3DXVECTOR3(x, y, z));
			}
			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				VList.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if ( szTemp[0] == 'u' )
		{
			char scanedString[1024];
			sscanf(szTemp, "%*s %s", scanedString);
			materialName = scanedString;
		}
		else if ( szTemp[0] == 'f' )
		{
			int aIndex[3][3] = { {0, }, {0, } };

			sscanf(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

		

			for ( int i = 0; i < 3; ++i )
			{
				VertexPNT v;

				v.p = VList[aIndex[i][0] - 1];
				v.t = VTList[aIndex[i][1] - 1];
				v.n = VNList[aIndex[i][2] - 1];

				

				if ( pmat )
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				PNTList.push_back(v);
			}
		}
	}

	for each( auto it in mapMaterialTexture )
	{
		SAFE_RELEASE(it.second);
	}

	mapMaterialTexture.clear();

	fclose(fp);

}

LPD3DXMESH OBJLoader::meshLoad(IN char* filename, 
	IN D3DXMATRIXA16* pmat,
	OUT vector<MaterialTexture*>& mtList)
{
	vector<D3DXVECTOR3> VList;
	vector<D3DXVECTOR2> VTList;
	vector<D3DXVECTOR3> VNList;
	vector<VertexPNT> PNTList;
	vector<DWORD> attrList;

	string materialName;

	FILE* fp = NULL;

	if (path.empty()) fopen_s(&fp, filename, "r");

	else
	{
		string fullPath;
		fullPath = path + filename;
		fopen_s(&fp, fullPath.c_str(), "r");
	}


	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf(szTemp, "%*s %s", szMtlPath);
			LoadMtlLib(szMtlPath);

			mtList.resize(mapMaterialTexture.size());

			for each(auto it in mapMaterialTexture)
			{
				mtList[it.second->getMTRef()] = it.second;
			}
		}

		else if (szTemp[0] == 'g')
		{
			if (PNTList.empty()) continue;
		}

		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == 't')
			{
				float u, v;
				sscanf(szTemp, "%*s %f %f %*f", &u, &v);
				VTList.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				VNList.push_back(D3DXVECTOR3(x, y, z));

			}
			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				VList.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char scanedString[1024];
			sscanf(szTemp, "%*s %s", scanedString);
			materialName = scanedString;
		}
		else if (szTemp[0] == 'f')
		{
			int aIndex[3][3];

			sscanf(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			attrList.push_back(mapMaterialTexture[materialName]->getMTRef());

			for (int i = 0; i < 3; ++i)
			{
				VertexPNT v;

				v.p = VList[aIndex[i][0] - 1];
				v.t = VTList[aIndex[i][1] - 1];
				v.n = VNList[aIndex[i][2] - 1];

				if (pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				PNTList.push_back(v);
			}
		}
	}

	LPD3DXMESH mesh;

	HRESULT hr = D3DXCreateMeshFVF(
		PNTList.size() / 3,
		PNTList.size(), 
		D3DXMESH_MANAGED, VertexPNT::FVF,
		D3DDevice, &mesh);

	VertexPNT* verBuffer = nullptr;
	mesh->LockVertexBuffer(0, (LPVOID*)&verBuffer);
	memcpy(verBuffer, &PNTList[0], PNTList.size() * sizeof(VertexPNT));
	mesh->UnlockVertexBuffer();

	WORD* indexBuffer = nullptr;
	mesh->LockIndexBuffer(0, (LPVOID*)&indexBuffer);
	for (int i = 0; i < PNTList.size(); ++i)
	{
		indexBuffer[i] = i;
	}
	mesh->UnlockIndexBuffer();

	DWORD* attrBuffer = nullptr;
	mesh->LockAttributeBuffer(0, &attrBuffer);
	memcpy(attrBuffer, &attrList[0], attrList.size() * sizeof(DWORD));
	mesh->UnlockAttributeBuffer();

	vector<DWORD> adjacencylnfo(mesh->GetNumFaces() * 3);
	mesh->GenerateAdjacency(0.0f, &adjacencylnfo[0]);

	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&adjacencylnfo[0], 0, 0, 0);



	/*VertexPNT* verBuffer;

	mesh->LockVertexBuffer(0, (LPVOID*)&verBuffer);

	for (int i = 0; i < PNTList.size(); i++)
	{
		verBuffer[i] = PNTList[i];
	}

	mesh->UnlockVertexBuffer();*/

	fclose(fp);

	return mesh;
}


void OBJLoader::LoadMtlLib ( char * filename )
{
	FILE* fp = NULL;
	

	if (path.empty())
		fopen_s(&fp, filename, "r");
	else {
		std::string fullPath;
		fullPath = path + filename;
		fopen_s(&fp, fullPath.c_str(), "r");
	}


	std::string sMtlName;
	int mtRef = 0;

	while ( true )
	{
		if ( feof ( fp ) )
			break;

		char szTemp[1024];

		fgets(szTemp, 1024, fp);

		if ( szTemp[0] == '#' )
		{
			continue;
		}
		else if ( szTemp[0] == 'n' )
		{
			char szMtlName[1024];
			sscanf ( szTemp, "%*s %s", szMtlName );
			sMtlName = szMtlName;

			SAFE_RELEASE(mapMaterialTexture[sMtlName]);
			mapMaterialTexture[sMtlName] = new MaterialTexture();
			mapMaterialTexture[sMtlName]->setMTRef(mtRef++);
		}
		else if ( szTemp[0] == 'K' )
		{
			if ( szTemp[1] == 'a' )
			{
				float r, g, b;
				sscanf(szTemp, "%*s %f %f %f", &r, &g, &b);
				D3DMATERIAL9& stMtl = mapMaterialTexture[sMtlName]->GetMaterial();
				stMtl.Ambient.r = r;
				stMtl.Ambient.g = g;
				stMtl.Ambient.b = b;
				stMtl.Ambient.a = 1.0f;
			}
			else if ( szTemp[1] == 'd' )
			{
				float r, g, b;
				sscanf ( szTemp, "%*s %f %f %f", &r, &g, &b );
				D3DMATERIAL9& stMtl = mapMaterialTexture[sMtlName]->GetMaterial ();
				stMtl.Diffuse.r = r;
				stMtl.Diffuse.g = g;
				stMtl.Diffuse.b = b;
				stMtl.Diffuse.a = 1.0f;
			}
			else if ( szTemp[1] == 's' )
			{
				float r, g, b;
				sscanf ( szTemp, "%*s %f %f %f", &r, &g, &b );
				D3DMATERIAL9& stMtl = mapMaterialTexture[sMtlName]->GetMaterial ();
				stMtl.Specular.r = r;
				stMtl.Specular.g = g;
				stMtl.Specular.b = b;
				stMtl.Specular.a = 1.0f;
			}
		}
		else if ( szTemp[0] == 'm' )
		{
			char szTexturePath[1024];
			sscanf ( szTemp, "%*s %s", szTexturePath );

			mapMaterialTexture[sMtlName]->SetTexture(TEXTMANAGER->getTextures(szTexturePath));
		}
	}

	fclose ( fp );
}
