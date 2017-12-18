#include "stdafx.h"
#include "OBJMap.h"

OBJMap::OBJMap(void)
{
}

OBJMap::~OBJMap(void)
{
	for each(auto it in mapVertex)
	{
		//SAFE_RELEASE(it);
	}
}

void OBJMap::Load(char * szFullPath, D3DXMATRIXA16 * pmat)
{
	FILE* fp = NULL;
	fopen_s(&fp, szFullPath, "r");

	vector<D3DXVECTOR3> vList;
	//vector<float> vIndexList;

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[66536];
		fgets(szTemp, 66536, fp);

		if (szTemp[0] == '#') continue;

		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == 't')
			{
				continue;
			}
			else if (szTemp[1] == 'n')
			{
				continue;
			}

			else // v
			{
				float x, y, z;
				sscanf(szTemp, "%*s %f %f %f", &x, &y, &z);
				D3DXVECTOR3 v = D3DXVECTOR3(x, y, z);
				
				vList.push_back(v);
			}
		}

		else if (szTemp[0] == 'f')
		{
			int aIndex[3];
			sscanf(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				D3DXVECTOR3 v = vList[aIndex[i] - 1];

				if (pmat)
				{
					D3DXVec3TransformCoord(&v, &v, pmat);
					//D3DXVec3TransformNormal(&v, &v, pmat);
				}
		
				mapVertex.push_back(v);
			}
		}
	}
	fclose(fp);
	
}

bool OBJMap::GetHeight(IN const float & x, OUT float & y, IN const float & z)
{
	
	D3DXVECTOR3 direc = { 0.0f, -1.0f, 0.0f };
	D3DXVECTOR3 ray = { x, 1000.0f, z };
	float u, v, distance;

	for (int i = 0; i < mapVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&mapVertex[i], &mapVertex[i + 1], &mapVertex[i + 2], &ray, &direc, &u, &v, &distance))
		{
			y = 1000.0f - distance;
		
			return true;
		}
	}
	return false;
}

void OBJMap::Render()
{
}
