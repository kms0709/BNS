#include "stdafx.h"

#include "AllocateHierarchy.h"
#include "MatrialTexture.h"

#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh()
	: root(nullptr)
	, animationController(nullptr)
	//, blendTime (0.3f)
	//, passedBlendTime(0.0f)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
{
}

SkinnedMesh::SkinnedMesh(char* szFolder, char* szFilename)
	: root(NULL)
	, animationController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
{
	SkinnedMesh* skinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);

	_rotaY = 0.0f;
	currentTime = 0;
	_stop = false;
	_start = false;

	D3DXMatrixIdentity(&body);
	D3DXMatrixTranslation(&tMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationY(&_ryMat, _rotaY);
	root = skinnedMesh->root;
	m_dwWorkingPaletteSize = skinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = skinnedMesh->m_pmWorkingPalette;
	D3DXMatrixScaling(&sMat, 1.0f, 1.0f, 1.0f);
	m_pEffect = skinnedMesh->m_pEffect;
	m_stBoundingSphere = skinnedMesh->m_stBoundingSphere;

	skinnedMesh->animationController->CloneAnimationController(
		skinnedMesh->animationController->GetMaxNumAnimationOutputs(),
		skinnedMesh->animationController->GetMaxNumAnimationSets(),
		skinnedMesh->animationController->GetMaxNumTracks(),
		skinnedMesh->animationController->GetMaxNumEvents(),
		&animationController);
}



SkinnedMesh::~SkinnedMesh()
{
	//AllocateHierarchy alloc;
	//D3DXFrameDestroy ( root, &alloc );

	SAFE_RELEASE ( animationController );
}

void SkinnedMesh::Load(const char* foldername, const char* filename)
{
	m_pEffect = LoadEffect("MultiAnimation.fx");

	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	std::string folder(foldername);
	std::string fullpath = foldername + std::string ( "\\" ) + filename;

	AllocateHierarchy alloc;
	alloc.setFolder(folder);
	alloc.setDefaultPaletteSize(nPaletteSize);

	m_stBoundingSphere.center = (alloc.getMinVector() + alloc.getMaxVector()) / 2.0f;
	m_stBoundingSphere.radi = D3DXVec3Length(&(alloc.getMinVector() - alloc.getMaxVector()));

	D3DXLoadMeshHierarchyFromXA(
		fullpath.c_str(),
		D3DXMESH_MANAGED,
		D3DDevice,
		&alloc,
		nullptr,
		(LPD3DXFRAME*)&root,
		&animationController
	);

	if ( m_pmWorkingPalette )
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = alloc.getMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];

	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	if (root)
		SetupBoneMatrixPtrs(root);
}

void SkinnedMesh::Update(Bone* frame, D3DXMATRIX* pmatParent)
{
	frame->CombinedTransformationMatrix = frame->TransformationMatrix;
	if (pmatParent)
	{
		frame->CombinedTransformationMatrix =
			frame->CombinedTransformationMatrix * (*pmatParent) ;
	}

	if (frame->pFrameSibling)
	{
		Update((Bone*)frame->pFrameSibling, pmatParent);
	}

	if (frame->pFrameFirstChild)
	{
		Update((Bone*)frame->pFrameFirstChild, &(frame->CombinedTransformationMatrix));
	}
}


void SkinnedMesh::SetupBoneMatrixPtrs ( LPD3DXFRAME frame)
{
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.
	if ( frame == nullptr )
		return;
	Bone* bone = ( Bone* ) frame;
	if ( bone->pMeshContainer )
	{
		BoneMesh* boneMesh = ( BoneMesh* ) bone->pMeshContainer;
		if ( boneMesh->pSkinInfo )
		{
			LPD3DXSKININFO skinInfo = boneMesh->pSkinInfo;
			DWORD dwNumBones = boneMesh->pSkinInfo->GetNumBones();
			for ( DWORD i = 0; i < dwNumBones; ++i )
			{
				LPCSTR szBoneName = skinInfo->GetBoneName(i);
				if ( szBoneName == NULL || strlen ( szBoneName ) == 0 )
					continue;

				Bone* p = (Bone*)D3DXFrameFind(root, skinInfo->GetBoneName(i));
				boneMesh->ppBoneMatrixPtrs[i] = &(p->CombinedTransformationMatrix);
			}
		}

	}

	//��������� ��� �����ӿ� ���ؼ� ����.
	if ( frame->pFrameFirstChild )
	{
		SetupBoneMatrixPtrs(frame->pFrameFirstChild);
	}

	if ( frame->pFrameSibling )
	{
		SetupBoneMatrixPtrs(frame->pFrameSibling);
	}
}

//void SkinnedMesh::UpdateSkinnedMesh ( LPD3DXFRAME frame)
//{
//	// pCurrentBoneMatrices �� ����Ͻÿ�
//	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
//
//	if ( frame == nullptr )
//		return;
//
//	Bone* bone = ( Bone* ) frame;
//	if ( bone->pMeshContainer )
//	{
//		BoneMesh* boneMesh = ( BoneMesh* ) bone->pMeshContainer;
//		if ( boneMesh->pSkinInfo )
//		{
//			LPD3DXSKININFO pSkinInfo = boneMesh->pSkinInfo;
//			DWORD dwNumBones = pSkinInfo->GetNumBones ();
//			for ( DWORD i = 0; i < dwNumBones; ++i )
//			{
//				boneMesh->pCurrentBoneMatrices[i] =
//					boneMesh->pBoneOffsetMatrices[i] *
//					*( boneMesh->ppBoneMatrixPtrs[i] );
//			}
//
//			BYTE* src = nullptr;
//			BYTE* dest = nullptr;
//
//			boneMesh->orgMesh->LockVertexBuffer ( D3DLOCK_READONLY, ( void** ) &src );
//			boneMesh->workMesh->LockVertexBuffer ( 0, ( void** ) &dest );
//
//			//MeshData.pMesh�� ������Ʈ �����ش�.
//			pSkinInfo->UpdateSkinnedMesh (
//				boneMesh->pCurrentBoneMatrices, nullptr, src, dest );
//
//			boneMesh->workMesh->UnlockVertexBuffer ();
//			boneMesh->orgMesh->UnlockVertexBuffer ();
//		}
//	}
//
//	//��������� ��� �����ӿ� ���ؼ� ����.
//	if ( frame->pFrameFirstChild )
//	{
//		UpdateSkinnedMesh ( frame->pFrameFirstChild );
//	}
//
//	if ( frame->pFrameSibling )
//	{
//		UpdateSkinnedMesh ( frame->pFrameSibling );
//	}
//
//}

void SkinnedMesh::UpdateAndRender ()
{
	if ( animationController )
	{
		animationController->AdvanceTime(TIMEMANAGER->getElapsedTime(), NULL);

		if (_stop)
		{
			// �ִϸ��̼� ����
			animationController->SetTrackWeight(0, 0);
		}

	}

	if ( root )
	{
		if (_rotaY >= PI2) _rotaY -= PI2;

		D3DXMatrixRotationY(&_ryMat, _rotaY);

		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		mat = sMat * _ryMat * mat * body;

		Update(root, &mat);
		Render(root);
	}

}

void SkinnedMesh::Render ( Bone* pBone )
{
	assert ( pBone );

	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	if ( pBone->pMeshContainer )
	{
		BoneMesh* pBoneMesh = ( BoneMesh* ) pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		D3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		D3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for ( DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib )
		{
			// set each transform into the palette
			for ( DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry )
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if ( dwMatrixIndex != UINT_MAX )
				{
					m_pmWorkingPalette[dwPalEntry] =
						pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] *
						(*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray("amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries);

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

			// set the technique we use to draw
			m_pEffect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin(&uiPasses, 0);
			for ( uiPass = 0; uiPass < uiPasses; ++uiPass )
			{
				m_pEffect->BeginPass(uiPass);
				pBoneMesh->workMesh->DrawSubset(dwAttrib);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//��������� ��� �����ӿ� ���ؼ� ����.
	if ( pBone->pFrameSibling )
	{
		Render((Bone*)pBone->pFrameSibling);
	}

	if ( pBone->pFrameFirstChild )
	{
		Render((Bone*)pBone->pFrameFirstChild);
	}
}

bool SkinnedMesh::getAniEnd(int index)
{
	if (!animationController) return false;

	if (!_start)
	{
		_start = true;
		// �ִϸ��̼��� ó�� ���������� ����
		// �̰� ���ϸ� �ִϸ��̼��� �̻���
		animationController->SetTrackPosition(0, 0.0f);
	}

	LPD3DXANIMATIONSET ani = nullptr;

	animationController->GetAnimationSet(index, &ani);
	
	float maxAniTime = ani->GetPeriod();

	//				�ð� ����
	currentTime += TIMEMANAGER->getElapsedTime();

	if (currentTime >= maxAniTime)
	{	
		currentTime = 0;
		
		_start = false;
		SAFE_RELEASE(ani);
		return true;
	}

	return false;
}

void SkinnedMesh::getMatrix(SkinnedMesh* skin, LPD3DXFRAME frame, LPCSTR groupName)
{
	//Bone* bone = (Bone*)frame;
	//if (bone == nullptr) bone = root;

	D3DXMATRIX group;

	Bone* p = (Bone*)D3DXFrameFind(root, groupName);
	group = p->CombinedTransformationMatrix;

	skin->setBodyMatrix(group);

//	if (bone->Name != NULL)
//	{
//		if (strcmp(groupName, bone->Name) == 0)
//		{
//			Bone* p = (Bone*)D3DXFrameFind(root, groupName);
//			group = p->CombinedTransformationMatrix;
//
//			skin->setBodyMatrix(group);
//		}
//	}
//	//��������� ��� �����ӿ� ���ؼ� ����.
//	if (bone->pFrameFirstChild)
//	{
//		getMatrix(skin, bone->pFrameFirstChild, groupName);
//	}
//
//	if (bone->pFrameSibling)
//	{
//		getMatrix(skin, bone->pFrameSibling, groupName);
//	}
}

void SkinnedMesh::SetAnimationIndex ( int index)
{
	if ( !animationController ) return;

	float time = animationController->GetTime();
	LPD3DXANIMATIONSET pAnimSet = NULL;
	animationController->GetAnimationSet(index, &pAnimSet);
	animationController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}

void SkinnedMesh::Destroy ()
{
	AllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)root, &ah);
	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}


void SkinnedMesh::SetRandomTrackPosition ()
{
	animationController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}

LPD3DXEFFECT SkinnedMesh::LoadEffect ( char* szFilename )
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	D3DDevice->GetDeviceCaps(&caps);
	if ( caps.VertexShaderVersion > D3DVS_VERSION ( 1, 1 ) )
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	HRESULT hr;
	if ( FAILED ( hr = D3DXCreateEffectFromFileA ( D3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer ) ) )
	{
		// if creation fails, and debug information has been returned, output debug info
		if ( pBuffer )
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}
