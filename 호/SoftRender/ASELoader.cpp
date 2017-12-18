#include "stdafx.h"
#include "ASELoader.h"
#include "ASEFrame.h"
#include "MatrialTexture.h"

ASELoader::ASELoader(void)
	: fileStream(NULL)
	, root (NULL)
{
}

ASELoader::~ASELoader(void)
{
}

ASEFrame* ASELoader::Load(IN char* filename, OUT ASEScene * pScene)
{

	fopen_s(&fileStream, filename, "r");

	if (fileStream == NULL)
	{
		//return NULL;	// 파일 없으면 NULL값 반환
	}

	while (true)
	{
		char* temp = GetToken();

		if (temp == NULL) break;

		if (IsEqual(temp, ID_SCENE))
		{
			if (pScene) ProcessSCENE(pScene);
		}

		else if (IsEqual(temp, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		
		else if (IsEqual(temp, ID_GEOMETRY))
		{
			ASEFrame* pFrame = ProcessGEOMOBJECT();
			if (root == NULL) root = pFrame;
		}

	}

	fclose(fileStream);

	root->CalcLocalTM(NULL);

	return root;
}

char* ASELoader::GetToken()
{ 
	bool isQuote = false;
	int nReadCount = 0;

	while (true)
	{
		unsigned char c = fgetc(fileStream);	// 파일의 값을 받옴

		if (feof(fileStream)) break;		// 파일의 끝이면 반복문 종료

		if (!isQuote && IsWhite(c))			//  isQuote가 false 이면서 문자의 아스키 값이 33보다 작을때
		{
			if (nReadCount == 0) continue;	//	읽은 숫자가 0이면 다시?
			else break;						//	아니면 종료
		}

		if (c == '\"') // 문자가 " 이면 
		{
			if (isQuote) break; // 닫는 따옴표면 멈춤

			isQuote = true;
			continue;
		}

		m_szToken[nReadCount++] = c;
	}

	if (nReadCount == 0)
	{
		return NULL;
	}// 다 돌았는데 읽은게 없으면 NULL값 반환

	m_szToken[nReadCount] = '\0';

	return m_szToken;
}

int ASELoader::GetInteger()
{
	return atoi(GetToken());
}

float ASELoader::GetFloat()
{
	return (float)atof(GetToken());
}

bool ASELoader::IsWhite(char c)
{
	return c < 33;
}

bool ASELoader::IsEqual(char* str1, char * str2)	// 같으면 true 아니면 false
{
	// strcmp = 같으면 0 반환
	if (strcmp(str1, str2) == 0) return true;
	else return false;
}

void ASELoader::SkipBlock()
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (szTemp == NULL) continue;

		if (IsEqual(szTemp, "{")) // 영역 지정하는거
		{
			++nLevel;
		}

		else if (IsEqual(szTemp, "}"))	// 영역 끝나는거
		{
			--nLevel;

		}

	} while (nLevel > 0);

}

void ASELoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();


		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;


		else if (IsEqual(szTemp, ID_MATERIAL_COUNT))
		{
			if (!materialTextureList.empty())
			{
				for each (auto it in materialTextureList)
				{
					SAFE_RELEASE(it);
				}
				materialTextureList.clear();
			}

			int size = GetInteger();
			materialTextureList.resize(size);
		}

		else if (IsEqual(szTemp, ID_MATERIAL))
		{
			int index = GetInteger();
			SAFE_RELEASE(materialTextureList[index]);
			materialTextureList[index] = new MaterialTexture;
			ProcessMATERIAL(materialTextureList[index]);
			materialTextureList.push_back(materialTextureList[index]);

			materialTextureList[index]->AutoRelease();
		}

	} while (nLevel > 0);
}

void ASELoader::ProcessMATERIAL(OUT MaterialTexture* pMtlTex)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) // 영역 지정하는거
		{
			++nLevel;
		}

		else if (IsEqual(szTemp, "}"))	// 영역 지정하는거
		{
			--nLevel;
		}

		else if (IsEqual(szTemp, ID_AMBIENT)) // 단어가 MATERIAL_AMBIENT  이면
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMaterial();
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}

		else if (IsEqual(szTemp, ID_DIFFUSE)) // 단어가 MATERIAL_DIFFUSE 면
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMaterial();
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}

		else if (IsEqual(szTemp, ID_SPECULAR)) // 단어가 MATERIAL_SPECULAR 이면
		{
			D3DMATERIAL9& stMtl = pMtlTex->GetMaterial();
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}

		else if (IsEqual(szTemp, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}

	} while (nLevel > 0);
}

void ASELoader::ProcessMAP_DIFFUSE(OUT MaterialTexture* pMtlTex)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) // 영역 지정하는거
		{
			++nLevel;
		}

		else if (IsEqual(szTemp, "}"))	// 영역 끝나는거
		{
			--nLevel;
		}

		else if (IsEqual(szTemp, ID_BITMAP))
		{
			char* fileName = GetToken();
			pMtlTex->SetTexture(TEXTMANAGER->getTextures(fileName));
		}

	} while (nLevel > 0);
}

ASEFrame* ASELoader::ProcessGEOMOBJECT()
{
	ASEFrame* frame = new ASEFrame;
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_NODE_NAME))
		{		
			char* szNodeName = GetToken();
			frameMap[szNodeName] = frame;
		}

		else if (IsEqual(szTemp, ID_NODE_PARENT))
		{
			char* szParentNodeName = GetToken();
			frameMap[szParentNodeName]->AddChild(frame);
		}

		else if (IsEqual(szTemp, ID_NODE_TM))
		{
			ProcessNODE_TM(frame);
		}

		else if (IsEqual(szTemp, ID_MESH))
		{
			ProcessMESH(frame);
		}
		else if (IsEqual(szTemp, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(frame);
		}
		else if (IsEqual(szTemp, ID_MATERIAL_REF))
		{
			frame->SetMaterialTexture(materialTextureList[GetInteger()]);
		}

	} while (nLevel > 0);

	frame->AutoRelease();

	return frame;
}

void ASELoader::ProcessMESH(OUT ASEFrame* pFrame)
{
	vector<D3DXVECTOR3> verPoint;
	vector<D3DXVECTOR2> vts;
	vector<VertexPNT> verPNT;

	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;


		else if (IsEqual(szTemp, ID_MESH_NUMVERTEX))
		{
			verPoint.resize(GetInteger());
		}

		else if (IsEqual(szTemp, ID_MESH_NUMFACES))
		{
			verPNT.resize(3 * GetInteger());
		}

		else if (IsEqual(szTemp, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(verPoint);
		}

		else if (IsEqual(szTemp, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(verPoint, verPNT);
		}

		else if (IsEqual(szTemp, ID_MESH_NUMTVERTEX)) vts.resize(GetInteger());

		else if (IsEqual(szTemp, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vts);
		}
		else if (IsEqual(szTemp, ID_MESH_NUMTVFACES))
		{
			GetToken();
		}

		else if (IsEqual(szTemp, ID_MESH_TFACELIST)) ProcessMESH_TFACELIST(vts, verPNT);


		else if (IsEqual(szTemp, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(verPNT);
		}

	} while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pFrame->GetWorldTM());

	for (int i = 0; i < verPNT.size(); ++i)
	{
		D3DXVec3TransformCoord(&verPNT[i].p, &verPNT[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&verPNT[i].n, &verPNT[i].n, &matInvWorld);
	}



	pFrame->SetPNTVerts(verPNT);
}

void ASELoader::ProcessMESH_VERTEX_LIST(OUT std::vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);

}

void ASELoader::ProcessMESH_FACE_LIST(IN std::vector<D3DXVECTOR3>& vecV, OUT std::vector<VertexPNT>& vecVertex)
{
	VertexPNT ver;

	vector<D3DXVECTOR3> position;
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_MESH_FACE))
		{
			int faceindex = GetInteger();

			GetToken();
			int numA = GetInteger();

			GetToken();
			int numB = GetInteger();

			GetToken();
			int numC = GetInteger();

			vecVertex[faceindex * 3 + 0].p = vecV[numA];
			vecVertex[faceindex * 3 + 1].p = vecV[numC];
			vecVertex[faceindex * 3 + 2].p = vecV[numB];

		}


	} while (nLevel > 0);

	for each(auto it in vecVertex)
	{
		for (int i = 0; i < position.size(); i++)
		{
			it.p = position[i];
		}
	}

}

void ASELoader::ProcessMESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& vecVT)		//text
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_MESH_TVERT))
		{
			int index = GetInteger();

			float u, v;

			u = GetFloat();
			v = GetFloat();

			v = 1 - v;

			vecVT[index] = D3DXVECTOR2(u, v);


		}


	} while (nLevel > 0);

}

void ASELoader::ProcessMESH_TFACELIST(IN std::vector<D3DXVECTOR2>& vecVT, OUT std::vector<VertexPNT>& vecVertex)	// text
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_MESH_TFACE))
		{
			int index = GetInteger();
			int numA = GetInteger();
			int numB = GetInteger();
			int numC = GetInteger();

			vecVertex[index * 3 + 0].t = vecVT[numA];
			vecVertex[index * 3 + 1].t = vecVT[numC];
			vecVertex[index * 3 + 2].t = vecVT[numB];
		}


	} while (nLevel > 0);
}

void ASELoader::ProcessMESH_NORMALS(OUT std::vector<VertexPNT>& vecVertex)
{
	int modCount[] = { 0, 2, 1 };
	int count = 0;
	int index = 0;
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_MESH_FACENORMAL))
		{
			index = GetInteger();
			count = 0;
		}

		else if (IsEqual(szTemp, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			float x, y, z;
			
			x = GetFloat();
			z = GetFloat();
			y = GetFloat();

			vecVertex[index * 3 + modCount[count]].n = D3DXVECTOR3(x, y, z);
			++count;
		}

	
	} while (nLevel > 0);
}

void ASELoader::ProcessNODE_TM(OUT ASEFrame* pFrame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	} while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);
}

void ASELoader::ProcessTM_ANIMATION(OUT ASEFrame * pFrame)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_POS_TRACK))
		{
			ProcessPOS_TRACK(pFrame);
		}
		else if (IsEqual(szTemp, ID_ROT_TRACK))
		{
			ProcessROT_TRACK(pFrame);
		}

	} while (nLevel > 0);
}

void ASELoader::ProcessPOS_TRACK(OUT ASEFrame * pFrame)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_POS_SAMPLE))
		{
			PositionSample positionSample;
			positionSample.n = GetInteger();

			float x, y, z;
			x = GetFloat();
			z = GetFloat();
			y = GetFloat();

			positionSample.v = D3DXVECTOR3(x, y, z);
			pFrame->posTrackList.push_back(positionSample);
		}


	} while (nLevel > 0);
}

void ASELoader::ProcessROT_TRACK(OUT ASEFrame * pFrame)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_ROT_SAMPLE))
		{
			RotationSample rotation;
			
			rotation.n = GetInteger();

			float x, y, z, w;

			x = GetFloat();
			z = GetFloat();
			y = GetFloat();
			w = GetFloat();

			rotation.q = D3DXQUATERNION(x, y, z, w);

			rotation.q.x *= sinf(rotation.q.w / 2.0f);
			rotation.q.y *= sinf(rotation.q.w / 2.0f);
			rotation.q.z *= sinf(rotation.q.w / 2.0f);
			rotation.q.w = cosf(rotation.q.w / 2.0f);

			if (!pFrame->rotTrackList.empty())
			{
				rotation.q = pFrame->rotTrackList.back().q * rotation.q;
			}

			pFrame->rotTrackList.push_back(rotation);

		}


	} while (nLevel > 0);
}

void ASELoader::ProcessSCENE(OUT ASEScene * pScene)
{
	int nLevel = 0;

	do
	{
		char* szTemp = GetToken();

		if (IsEqual(szTemp, "{")) ++nLevel;
		else if (IsEqual(szTemp, "}")) --nLevel;

		else if (IsEqual(szTemp, ID_FIRSTFRAME))
		{
			pScene->firstFrame = GetInteger();
		}

		else if (IsEqual(szTemp, ID_LASTFRAME))
		{
			pScene->lastFrame = GetInteger();
		}

		else if (IsEqual(szTemp, ID_FRAMESPEED))
		{
			pScene->frameSpeed = GetInteger();
		}

		else if (IsEqual(szTemp, ID_TICKSPERFRAME))
		{
			pScene->ticksPerFrame = GetInteger();
		}


	} while (nLevel > 0);
}
