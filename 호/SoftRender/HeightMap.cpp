#include "stdafx.h"
#include "HeightMap.h"

HeightMap::HeightMap()
	: texture(nullptr)
	, mesh(nullptr)
{
}

HeightMap::~HeightMap()
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(mesh);
}

void HeightMap::Load(char* szFullPath, D3DXMATRIXA16* pmat)
{
	VertexPNT verPNT;
	vector<VertexPNT> vecPNT;
	
	vector<DWORD> indexList;

	FILE* fp = nullptr;

	fopen_s(&fp, szFullPath, "rb");

	for (int z = 0; z < VER_N; z++)
	{
		for (int x = 0; x < VER_N; x++)
		{
			float y = ((unsigned char)fgetc(fp)) / 10.0f;

			int index = z * VER_N + x;		
	
			verPNT.p = D3DXVECTOR3(x, y, z);
			verPNT.n = D3DXVECTOR3(0, 1, 0);
			verPNT.t = D3DXVECTOR2(x / (float)TILE_N, z / (float)TILE_N);
	
			/*if (pmat)
			{
				D3DXVec3TransformCoord(&verPNT.p, &verPNT.p, pmat);
				D3DXVec3TransformNormal(&verPNT.n, &verPNT.n, pmat);
			}*/

			verts.push_back(verPNT.p);
			vecPNT.push_back(verPNT);
		}
	}

	for (int z = 1; z < VER_N - 1; z++)
	{
		for (int x = 1; x < VER_N - 1; x++)
		{
			D3DXVECTOR3 LR = vecPNT[(x + 1) + z * VER_N].p - vecPNT[(x - 1) + z * VER_N].p;
			D3DXVECTOR3 TB = vecPNT[x + (z + 1) * VER_N].p - vecPNT[x + (z - 1) * VER_N].p;

			D3DXVec3Cross(&vecPNT[x + z * VER_N].n, &TB, &LR);

			D3DXVec3Normalize(&vecPNT[x + z * VER_N].n, &vecPNT[x + z * VER_N].n);

			//if (pmat) D3DXVec3TransformNormal(&vecPNT[x + z * VER_N].n, &vecPNT[x + z * VER_N].n, pmat);
		}
	}

	for (int z = 0; z < TILE_N; z++)
	{
		for (int x = 0; x < TILE_N; x++)
		{
			int index_0 = x + (z + 1) * VER_N;
			int index_1 = x + z * VER_N;
			int index_2 = (x + 1) + (z + 1) * VER_N;
			int index_3 = (x + 1) + z * VER_N;

			indexList.push_back(index_0);
			indexList.push_back(index_1);
			indexList.push_back(index_2);

			indexList.push_back(index_3);
			indexList.push_back(index_2);
			indexList.push_back(index_1);
		}
	}

	fclose(fp);
	
	HRESULT hr = D3DXCreateMeshFVF(
		TILE_N * TILE_N * 2,
		VER_N * VER_N,
		D3DXMESH_MANAGED | D3DXMESH_32BIT, 
		VertexPNT::FVF,
		D3DDevice, &mesh);
	
	VertexPNT* verBuffer = nullptr;
	mesh->LockVertexBuffer(0, (LPVOID*)&verBuffer);
	memcpy(verBuffer, &vecPNT[0], vecPNT.size() * sizeof(VertexPNT));
	mesh->UnlockVertexBuffer();
	
	DWORD* indexBuffer = nullptr;
	mesh->LockIndexBuffer(0, (LPVOID*)&indexBuffer);

	memcpy(indexBuffer, &indexList[0], indexList.size() * sizeof(DWORD));
	
	mesh->UnlockIndexBuffer();
	
	DWORD* attrBuffer = nullptr;
	mesh->LockAttributeBuffer(0, &attrBuffer);

	for (int i = 0; i < TILE_N * 2; i++)
	{
		attrBuffer[i] = 0;
	}
	
	mesh->UnlockAttributeBuffer();
	
	vector<DWORD> adjacencylnfo(mesh->GetNumFaces() * 3);
	mesh->GenerateAdjacency(0.0f, &adjacencylnfo[0]);
	
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&adjacencylnfo[0], 0, 0, 0);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 0.3f;
	material.Ambient.g = 0.3f;
	material.Ambient.b = 0.3f;
	material.Ambient.a = 1.0f;

	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;

	material.Specular.r = 0.7f;
	material.Specular.g = 0.7f;
	material.Specular.b = 0.7f;
	material.Specular.a = 1.0f;
}

bool HeightMap::GetHeight(IN const float& x, OUT float& y, IN const float& z)
{
	if (x < 0 ||
		z < 0 ||
		x > TILE_N ||
		z > TILE_N) return false;


	int col = floorf(x);
	int row = floorf(z);

	float dx = x - col;
	float dz = z - row;

	D3DXVECTOR3 index_A = verts[row * VER_N + col];
	D3DXVECTOR3 index_B = verts[row * VER_N + col + 1];
	D3DXVECTOR3 index_C = verts[(row + 1) * VER_N + col];
	D3DXVECTOR3 index_D = verts[(row + 1) * VER_N + col + 1];

	if (1.0f - dx > dz)
	{
		D3DXVECTOR3 uy = (index_C - index_A) * dz;
		D3DXVECTOR3 vy = (index_B - index_A) * dx;

		y = (uy + vy).y + index_A.y;
	}

	else
	{
		D3DXVECTOR3 uy = (index_B - index_D) * (1.0f - dz);
		D3DXVECTOR3 vy = (index_C - index_D) * (1.0f - dx);

		y = (uy + vy).y + index_D.y;
	}
	

	return true;
}

void HeightMap::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);


	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DDevice->SetMaterial(&material);
	D3DDevice->SetTexture(0, this->texture);
		
	mesh->DrawSubset(0);
}

