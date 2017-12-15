#include "stdafx.h"
#include "MaterialTexture.h"
#include "AllocateHierarchy.h"


AllocateHierarchy::AllocateHierarchy()
	: folder( L"" )
	, defaultPaletteSize( 0 )
	, maxPaletteSize( 0 )
	, minVector( 0, 0, 0 )
	, maxVector( 0, 0, 0 )
{
}


AllocateHierarchy::~AllocateHierarchy()
{
}

STDMETHODIMP AllocateHierarchy::CreateFrame( LPCSTR Name, LPD3DXFRAME * ppNewFrame )
{
	Bone* frame = new Bone;

	frame->Name = NULL;
	if ( Name )
	{
		frame->Name = new char[ strlen( Name ) + 1 ];
		strcpy( frame->Name, Name );
	}

	frame->pFrameFirstChild = nullptr;
	frame->pFrameSibling = nullptr;
	frame->pMeshContainer = nullptr;

	D3DXMatrixIdentity( &frame->TransformationMatrix );
	D3DXMatrixIdentity( &frame->CombinedTransformationMatrix );

	*ppNewFrame = frame;

	return S_OK;

}

STDMETHODIMP AllocateHierarchy::CreateMeshContainer(
	LPCSTR Name,
	CONST D3DXMESHDATA * pMeshData,
	CONST D3DXMATERIAL * pMaterials,
	CONST D3DXEFFECTINSTANCE * pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD * pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER * ppNewMeshContainer )
{

	assert( pMeshData && pMeshData->Type == D3DXMESHTYPE_MESH );

	// �޽� �����̳� ����
	BoneMesh* pBoneMesh = new BoneMesh;

	// �̸� ����
	pBoneMesh->Name = NULL;


	for ( DWORD i = 0; i < NumMaterials; ++i )
	{
		// �������� ����
		pBoneMesh->vecMaterial.push_back( pMaterials[ i ].MatD3D );
		// �ؽ��� ���� ����.
		wchar_t sfileName[ 256 ];
		int len = ( int ) strlen( pMaterials[ i ].pTextureFilename ) + 1;
		mbstowcs( sfileName, pMaterials[ i ].pTextureFilename, len );
		wstring sFullPath = folder + wstring( L"/" ) + sfileName;
		LPDIRECT3DTEXTURE9 pTex = MANAGER_TEXTURE->GetTexture( sFullPath );
		pBoneMesh->vecTexture.push_back( pTex );
	}

	// ����Ʈ ����
	pBoneMesh->pEffects = nullptr;

	// �������� ����
	if ( pAdjacency )
	{
		DWORD dwNumFaces = pMeshData->pMesh->GetNumFaces();
		pBoneMesh->pAdjacency = new DWORD[ 3 * dwNumFaces ];
		memcpy( pBoneMesh->pAdjacency, pAdjacency, 3 * sizeof( DWORD ) * dwNumFaces );
	}


	// step 1. pSkinInfo ����
	SAFE_ADDREF( pSkinInfo );
	pBoneMesh->pSkinInfo = pSkinInfo;

	// step 2. �޽� ����
	//SAFE_ADDREF ( pMeshData->pMesh );
	//pBoneMesh->orgMesh = pMeshData->pMesh;
	//pBoneMesh->orgMesh->CloneMeshFVF (
	//	pBoneMesh->orgMesh->GetOptions (),
	//	pBoneMesh->orgMesh->GetFVF (),
	//	D3DDevice,
	//	&pBoneMesh->workMesh );

	if ( pMeshData && pMeshData->pMesh )
	{
		D3DXVECTOR3 vMin( 0, 0, 0 ), vMax( 0, 0, 0 );
		LPVOID pV = NULL;

		pMeshData->pMesh->LockVertexBuffer( 0, &pV );
		D3DXComputeBoundingBox( ( D3DXVECTOR3* ) pV,
			pMeshData->pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize( pMeshData->pMesh->GetFVF() ),
			&vMin,
			&vMax );
		D3DXVec3Minimize( &minVector, &minVector, &vMin );
		D3DXVec3Maximize( &maxVector, &maxVector, &vMax );
		pMeshData->pMesh->UnlockVertexBuffer();

		pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF(),
			D3DDevice,
			&pBoneMesh->orgMesh );
	}




	// step 3. pSkinInfo->GetNumBones()�� ����
	// ������� ��ġ�� ��� ���� ���� ��Ʈ���� ���� ����
	// ppBoneMatrixPtrs, pBoneOffsetMatrices, pCurrentBoneMatrices�� �����Ҵ�
	//DWORD dwNumBones = pSkinInfo->GetNumBones ();
	//pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
	//pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
	//pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];

	//// step 4. ���� �Ҵ�� pBoneOffsetMatrices ��Ʈ������ �� ����.
	//// pSkinInfo->GetBoneOffsetMatrix(i)
	//for ( DWORD i = 0; i < dwNumBones; ++i )
	//{
	//	pBoneMesh->pBoneOffsetMatrices[i] = *( pSkinInfo->GetBoneOffsetMatrix ( i ) );
	//}
	//pBoneMesh->pEffects = NULL;
	//pBoneMesh->pAdjacency = NULL;

	if ( pSkinInfo )
	{
		// pSkinInfo->GetNumBones()�� ���� ������� ��ġ�� ��� ���� ���� ��Ʈ���� ���� ����
		// ppBoneMatrixPtrs, pBoneOffsetMatrices�� �����Ҵ�
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[ dwNumBones ];
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[ dwNumBones ];
		pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[ dwNumBones ];
		for ( DWORD i = 0; i < dwNumBones; ++i )
		{
//			pBoneMesh->pBoneOffsetMatrices[ i ] = *( pBoneMesh->pSkinInfo->GetBoneOffsetMatrix( i ) );
			pBoneMesh->ppBoneMatrixPtrs[ i ] = NULL;
			pBoneMesh->pBoneOffsetMatrices[ i ] = *( pSkinInfo->GetBoneOffsetMatrix( i ) );
		}

		// ConvertToIndexedBlendedMesh �Լ��� �ȷ�Ʈ ��Ʈ�� ������ �Ѱܾ��ϱ� ������ 
		// ��������� �����ϰ� �ܺο��� �������ֵ��� ����.
		// �޽��� ������ �ִ� �ȷ�Ʈ�� ������ 
		// m_dwDefaultPaletteSize�� pSkinInfo->GetNumBones()���� Ŭ �� ����.
		// m_dwDefaultPaletteSize�� ���̴��� ���ǵǾ��ִ�.
		pBoneMesh->dwNumPaletteEntries = min( defaultPaletteSize, pSkinInfo->GetNumBones() );

		// �ִ� �ȷ�Ʈ ������ ������Ʈ
		if ( maxPaletteSize < pBoneMesh->dwNumPaletteEntries )
		{
			maxPaletteSize = pBoneMesh->dwNumPaletteEntries;
		}

		// blend weights�� �ε����� �̿��� workMesh ����.
		pBoneMesh->pSkinInfo->ConvertToIndexedBlendedMesh(
			pBoneMesh->orgMesh,
			D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
			pBoneMesh->dwNumPaletteEntries,
			pBoneMesh->pAdjacency,
			NULL,
			NULL,
			NULL,
			&pBoneMesh->dwMaxNumFaceInfls,
			&pBoneMesh->dwNumAttrGroups,
			&pBoneMesh->pBufBoneCombos,
			&pBoneMesh->workMesh );

		// ���� �޽��� FVF�� ���ؽ� ���� ������ ���� �� �� ���� ��� FVF�� �����Ѵ�
		DWORD dwOldFVF = pBoneMesh->workMesh->GetFVF();
		DWORD dwNewFVF =
			( dwOldFVF & D3DFVF_POSITION_MASK ) |
			D3DFVF_NORMAL |
			D3DFVF_TEX1 |
			D3DFVF_LASTBETA_UBYTE4;

		if ( dwNewFVF != dwOldFVF )
		{
			// �޽��� �����ϸ鼭 FVF�� �����Ѵ�.
			LPD3DXMESH pMesh = NULL;

			pBoneMesh->workMesh->CloneMeshFVF(
				pBoneMesh->workMesh->GetOptions(),
				dwNewFVF,
				D3DDevice,
				&pMesh );

			// ���� �޽��� ��ü
			SAFE_RELEASE( pBoneMesh->workMesh );
			pBoneMesh->workMesh = pMesh;

			// ���� ������ �޽����� ��� ������ �����Ƿ�
			// ���� �޽� FVF�� ��� ������ ������ ���� ����������.
			if ( !( dwOldFVF & D3DFVF_NORMAL ) )
			{
				D3DXComputeNormals( pBoneMesh->workMesh, NULL );
			}
		}

		// Interpret the UBYTE4 as a D3DCOLOR.
		// The GeForce3 doesn't support the UBYTE4 decl type.  So, we convert any
		// blend indices to a D3DCOLOR semantic, and later in the shader convert
		// it back using the D3DCOLORtoUBYTE4() intrinsic.  Note that we don't
		// convert any data, just the declaration.
		D3DVERTEXELEMENT9 pDecl[ MAX_FVF_DECL_SIZE ];
		D3DVERTEXELEMENT9 * pDeclCur;
		pBoneMesh->workMesh->GetDeclaration( pDecl );

		pDeclCur = pDecl;
		while ( pDeclCur->Stream != 0xff )
		{
			if ( ( pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES ) &&
				( pDeclCur->UsageIndex == 0 ) )
				pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
			pDeclCur++;
		}
		pBoneMesh->workMesh->UpdateSemantics( pDecl );
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;

}

STDMETHODIMP AllocateHierarchy::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	// TODO : ���� �� �սô�.
	Bone* bone = ( Bone* ) pFrameToFree;

	SAFE_DELETE_ARRAY( bone->Name );
	SAFE_DELETE( bone );

	return S_OK;

}

STDMETHODIMP AllocateHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	// TODO : ���� �� �սô�.

	BoneMesh* boneMesh = ( BoneMesh* ) pMeshContainerToFree;

	SAFE_RELEASE( boneMesh->pSkinInfo );
	SAFE_RELEASE( boneMesh->workMesh );
	SAFE_RELEASE( boneMesh->orgMesh );
	SAFE_RELEASE( boneMesh->pBufBoneCombos );

	SAFE_DELETE_ARRAY( boneMesh->Name );
	SAFE_DELETE_ARRAY( boneMesh->pAdjacency );
	SAFE_DELETE_ARRAY( boneMesh->ppBoneMatrixPtrs );
	SAFE_DELETE_ARRAY( boneMesh->pBoneOffsetMatrices );

	SAFE_DELETE( pMeshContainerToFree );
	return S_OK;

}
