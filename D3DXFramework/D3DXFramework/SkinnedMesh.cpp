#include "stdafx.h"

#include "AllocateHierarchy.h"
#include "MaterialTexture.h"

#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh()
	: root( nullptr )
	, animationController( nullptr )
	, blendTime( 0.3f )
	, passedBlendTime( 0.0f )
	, m_dwWorkingPaletteSize( 0 )
	, m_pmWorkingPalette( NULL )
	, m_pEffect( NULL )
	, m_vPosition( 0, 0, 0 )
	, m_fRot( 0, 0, 0 )
{
	//	D3DXMatrixIdentity( &rootMatrix );
}

SkinnedMesh::SkinnedMesh( wchar_t* szFolder, wchar_t* szFilename )
	: root( NULL )
	, animationController( NULL )
	, blendTime( 0.3f )
	, passedBlendTime( 0.0f )
	, m_dwWorkingPaletteSize( 0 )
	, m_pmWorkingPalette( NULL )
	, m_pEffect( NULL )
	, m_vPosition( 0, 0, 0 )
	, m_fRot( 0, 0, 0 )
{
	SkinnedMesh* skinnedMesh = MANAGER_SKINNED->GetSkinnedMesh( szFolder, szFilename );

	D3DXMatrixIdentity( &rootMatrix );
	D3DXMatrixIdentity( &matWorld );
	root = skinnedMesh->root;
	m_dwWorkingPaletteSize = skinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = skinnedMesh->m_pmWorkingPalette;
	m_pEffect = skinnedMesh->m_pEffect;
	m_stBoundingSphere = skinnedMesh->m_stBoundingSphere;

	if ( skinnedMesh->animationController )
	{
		skinnedMesh->animationController->CloneAnimationController(
			skinnedMesh->animationController->GetMaxNumAnimationOutputs(),
			skinnedMesh->animationController->GetMaxNumAnimationSets(),
			skinnedMesh->animationController->GetMaxNumTracks(),
			skinnedMesh->animationController->GetMaxNumEvents(),
			&animationController );
	}
}



SkinnedMesh::~SkinnedMesh()
{
	//AllocateHierarchy alloc;
	//D3DXFrameDestroy ( root, &alloc );

	SAFE_RELEASE( animationController );
}

void SkinnedMesh::Load( const wchar_t * foldername, const wchar_t * filename )
{
	m_pEffect = LoadEffect( L"./data/MultiAnimation.fx" );

	int nPaletteSize = 0;
	m_pEffect->GetInt( "MATRIX_PALETTE_SIZE", &nPaletteSize );

	wstring folder( foldername );
	wstring fullpath = foldername + wstring( L"/" ) + filename;

	AllocateHierarchy alloc;
	alloc.SetFolder( folder );
	alloc.SetDefaultPaletteSize( nPaletteSize );

	m_stBoundingSphere.vCenter = ( alloc.GetMinVector() + alloc.GetMaxVector() ) / 2.0f;
	m_stBoundingSphere.fRadius = D3DXVec3Length( &( alloc.GetMinVector() - alloc.GetMaxVector() ) );

	D3DXLoadMeshHierarchyFromX(
		fullpath.c_str(),
		D3DXMESH_MANAGED,
		D3DDevice,
		&alloc,
		nullptr,
		( LPD3DXFRAME* ) &root,
		&animationController
	);

	if ( m_pmWorkingPalette )
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = alloc.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[ m_dwWorkingPaletteSize ];

	for ( DWORD i = 0; i < m_dwWorkingPaletteSize; ++i )
	{
		D3DXMatrixIdentity( &m_pmWorkingPalette[ i ] );
	}
	if ( m_pmWorkingPalette == NULL )
	{
		m_dwWorkingPaletteSize = 0;
	}

	if ( root )
		SetupBoneMatrixPtrs( root );

}

void SkinnedMesh::Update( Bone* frame, D3DXMATRIX* pmatParent )
{
	frame->CombinedTransformationMatrix = frame->TransformationMatrix;
	if ( pmatParent )
	{
		frame->CombinedTransformationMatrix =
			frame->CombinedTransformationMatrix * ( *pmatParent );
	}

	if ( frame->pFrameSibling )
	{
		Update( ( Bone* ) frame->pFrameSibling, pmatParent );
	}

	if ( frame->pFrameFirstChild )
	{
		Update( ( Bone* ) frame->pFrameFirstChild, &( frame->CombinedTransformationMatrix ) );
	}
}


void SkinnedMesh::SetupBoneMatrixPtrs( LPD3DXFRAME frame )
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.
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
				LPCSTR szBoneName = skinInfo->GetBoneName( i );
				if ( szBoneName == NULL || strlen( szBoneName ) == 0 )
					continue;

				Bone* p = ( Bone* ) D3DXFrameFind( root, skinInfo->GetBoneName( i ) );
				boneMesh->ppBoneMatrixPtrs[ i ] = &( p->CombinedTransformationMatrix );
			}
		}

	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if ( frame->pFrameFirstChild )
	{
		SetupBoneMatrixPtrs( frame->pFrameFirstChild );
	}

	if ( frame->pFrameSibling )
	{
		SetupBoneMatrixPtrs( frame->pFrameSibling );
	}

}

//void SkinnedMesh::UpdateSkinnedMesh( Bone* bone )
//{
//	// pCurrentBoneMatrices 를 계산하시오
//	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
//
//	if ( bone == nullptr )
//		return;
//
//	if ( bone->pMeshContainer )
//	{
//		BoneMesh* pBoneMesh = ( BoneMesh* ) bone->pMeshContainer;
//		if ( pBoneMesh->pSkinInfo )
//		{
//			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
//
//			DWORD num = pSkinInfo->GetNumBones();
//
//			for ( DWORD i = 0; i < num; ++i )
//			{
//				pBoneMesh->pCurrentBoneMatrices[ i ] =
//					pBoneMesh->pBoneOffsetMatrices[ i ] *
//					( *pBoneMesh->ppBoneMatrixPtrs[ i ] );
//			}
//
//			BYTE* src = nullptr;
//			BYTE* dest = nullptr;
//
//			pBoneMesh->orgMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** ) &src );
//			pBoneMesh->workMesh->LockVertexBuffer( 0, ( void** ) &dest );
//
//			//MeshData.pMesh을 업데이트 시켜준다.
//			pSkinInfo->UpdateSkinnedMesh(
//				pBoneMesh->pCurrentBoneMatrices, nullptr, src, dest );
//
//			pBoneMesh->workMesh->UnlockVertexBuffer();
//			pBoneMesh->orgMesh->UnlockVertexBuffer();
//		}
//	}
//
//	//재귀적으로 모든 프레임에 대해서 실행.
//	if ( bone->pFrameFirstChild )
//	{
//		UpdateSkinnedMesh( ( Bone* ) bone->pFrameFirstChild );
//	}
//
//	if ( bone->pFrameSibling )
//	{
//		UpdateSkinnedMesh( ( Bone* ) bone->pFrameSibling );
//	}
//
//}

void SkinnedMesh::Update()
{
	UpdatePivot();

	if ( root )
	{
		Update( root, NULL );
	}
}

void SkinnedMesh::UpdatePivot()
{

	D3DXMATRIX matRotX, matRotY, matRotZ;
	D3DXMatrixRotationX( &matRotX, m_fRot.x );
	D3DXMatrixRotationY( &matRotY, m_fRot.y );
	D3DXMatrixRotationZ( &matRotZ, m_fRot.z );

	D3DXMATRIX matPos;
	D3DXMatrixTranslation( &matPos, m_vPosition.x, m_vPosition.y, m_vPosition.z );

	rootMatrix = matRotX * matRotY * matRotZ * matPos;
}

void SkinnedMesh::AnimationUpdate()
{
	if ( animationController )
	{
		animationController->AdvanceTime( MANAGER_TIME->GetElapsedTime(), NULL );
	}

	// 블렌드 설정
	if ( passedBlendTime <= blendTime )
	{
		passedBlendTime += MANAGER_TIME->GetElapsedTime();

		// 끝날때까지 계산
		if ( passedBlendTime < blendTime )
		{
			float fWeight = passedBlendTime / blendTime;

			animationController->SetTrackWeight( 0, fWeight );
			animationController->SetTrackWeight( 1, 1.0f - fWeight );
		}
		// 끝나면 꺼줌
		else
		{
			animationController->SetTrackWeight( 0, 1 );
			animationController->SetTrackWeight( 1, 0 );

			animationController->SetTrackEnable( 1, false );
		}
	}
}

void SkinnedMesh::Render()
{
	if ( root )
	{
		Render( root );
		//BoundingSphereDraw();
	}
}

void SkinnedMesh::Render( Bone* pBone )
{
	assert( pBone );

	//	D3DDEVICE->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if ( pBone->pMeshContainer )
	{
		BoneMesh* pBoneMesh = ( BoneMesh* ) pBone->pMeshContainer;

		LPD3DXBONECOMBINATION pBoneCombos;

		// get bone combinations
		if ( pBoneMesh->pBufBoneCombos )
		{
			pBoneCombos = ( LPD3DXBONECOMBINATION ) ( pBoneMesh->pBufBoneCombos->GetBufferPointer() );
		}
		else
		{
			pBoneCombos = nullptr;
		}

		D3DXMATRIXA16 matViewProj, matView, matProj;
		D3DDevice->GetTransform( D3DTS_VIEW, &matView );
		D3DDevice->GetTransform( D3DTS_PROJECTION, &matProj );
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		D3DDevice->GetTransform( D3DTS_VIEW, &mView );
		D3DXMatrixInverse( &mInvView, 0, &mView );
		D3DXVECTOR3 vEye = D3DXVECTOR3( 0, 0, 0 );
		D3DXVec3TransformCoord( &vEye, &vEye, &mInvView );

		// for each palette
		for ( DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib )
		{
			// set each transform into the palette
			for ( DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry )
			{
				DWORD dwMatrixIndex = pBoneCombos[ dwAttrib ].BoneId[ dwPalEntry ];
				if ( dwMatrixIndex != UINT_MAX )
				{
					m_pmWorkingPalette[ dwPalEntry ] = 
						pBoneMesh->pBoneOffsetMatrices[ dwMatrixIndex ] *
						( *pBoneMesh->ppBoneMatrixPtrs[ dwMatrixIndex ] ) * rootMatrix * matWorld;
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray( "amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries );

			m_pEffect->SetMatrix( "g_mViewProj", &matViewProj );
			m_pEffect->SetVector( "vLightDiffuse", &D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
			m_pEffect->SetVector( "vWorldLightPos", &D3DXVECTOR4( 500.0f, 500.0f, 500.0f, 1.0f ) );
			m_pEffect->SetVector( "vWorldCameraPos", &D3DXVECTOR4( vEye, 1.0f ) );
			m_pEffect->SetVector( "vMaterialAmbient", &D3DXVECTOR4( 0.53f, 0.53f, 0.53f, 0.53f ) );
			m_pEffect->SetVector( "vMaterialDiffuse", &D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture( "g_txScene", pBoneMesh->vecTexture[ pBoneCombos[ dwAttrib ].AttribId ] );

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt( "CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1 );

			// set the technique we use to draw
			m_pEffect->SetTechnique( "Skinning20" );

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin( &uiPasses, 0 );
			for ( uiPass = 0; uiPass < uiPasses; ++uiPass )
			{
				m_pEffect->BeginPass( uiPass );
				pBoneMesh->workMesh->DrawSubset( dwAttrib );
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if ( pBone->pFrameSibling )
	{
		Render( ( Bone* ) pBone->pFrameSibling );
	}

	if ( pBone->pFrameFirstChild )
	{
		Render( ( Bone* ) pBone->pFrameFirstChild );
	}
}

void SkinnedMesh::BoundingSphereDraw()
{
	if ( m_stBoundingSphere.fRadius )
	{
		LPD3DXMESH mesh;
		D3DXCreateSphere( D3DDevice, m_stBoundingSphere.fRadius, 20, 20, &mesh, NULL );

		D3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
		D3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		D3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		D3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

		mesh->DrawSubset( 0 );

		D3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
		D3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		D3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	}
}


void SkinnedMesh::SetAnimationIndex( int index, bool isBlend )
{
	if ( !animationController )
		return;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	animationController->GetAnimationSet( index, &pAnimSet );

	// 블렌드 설정
	if ( isBlend )
	{
		// 블렌드를 할려면 이전 애니메이션도 구해야한다.
		LPD3DXANIMATIONSET pPrevAnimSet = NULL;

		animationController->GetTrackAnimationSet( 0, &pPrevAnimSet );	// 0번째 트랙을 이전(현재) 트랙에 담는다.
		animationController->SetTrackAnimationSet( 1, pPrevAnimSet );

		// GetTrackDesc 으로 현재 트랙에 다음 트랙에 대한 정보를 넣어준다.
		// GetTrackDesc 0, 1
		// 0, 0.0f
		// 1, 1.0f
		D3DXTRACK_DESC stTrackDest;
		animationController->GetTrackDesc( 0, &stTrackDest );	// 0번째 트랙의 정보를 stTrackDest에 담는다.
		animationController->SetTrackDesc( 1, &stTrackDest );	// 1번째 트랙의 정보에 stTrackDest를 넣는다.

		// weight의 값은 0 ~ 1
		// weight 넣어주기
		animationController->SetTrackWeight( 0, 0.0f );	// 0번째 트랙 가중치(무게)에 0.0f 를 설정한다.
		animationController->SetTrackWeight( 1, 1.0f );	// 1번째 트랙 가중치(무게)에 1.0f 를 설정한다.

		animationController->SetTrackAnimationSet( 1, pPrevAnimSet );	// 1번째 트랙에 이전(현재) 트랙을 담는다.
		SAFE_RELEASE( pPrevAnimSet );

		passedBlendTime = 0.0f;
	}

	animationController->SetTrackAnimationSet( 0, pAnimSet );
	SAFE_RELEASE( pAnimSet );

}

void SkinnedMesh::Destroy()
{
	AllocateHierarchy ah;
	D3DXFrameDestroy( ( LPD3DXFRAME ) root, &ah );
	SAFE_DELETE_ARRAY( m_pmWorkingPalette );
	SAFE_RELEASE( m_pEffect );
}

//void SkinnedMesh::SetMatrices( IN LPD3DXFRAME frame, IN LPSTR boneName )
//{
//	Bone* bone = ( Bone* ) D3DXFrameFind( frame, boneName );
//	rootMatrix = bone->CombinedTransformationMatrix;
//}

//void SkinnedMesh::SetBone( IN LPD3DXFRAME frame, IN LPSTR boneName, IN LPSTR rootBoneName )
//{
//	Bone* bone = ( Bone* )D3DXFrameFind( frame, boneName );
//	Bone* rootBone = ( Bone* )D3DXFrameFind( root, rootBoneName );
//
//	rootBone->CombinedTransformationMatrix = bone->CombinedTransformationMatrix;
//}

void SkinnedMesh::SetRandomTrackPosition()
{
	animationController->SetTrackPosition( 0, ( rand() % 100 ) / 10.0f );
}

LPD3DXEFFECT SkinnedMesh::LoadEffect( wchar_t* szFilename )
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[ 2 ] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	D3DDevice->GetDeviceCaps( &caps );
	if ( caps.VertexShaderVersion > D3DVS_VERSION( 1, 1 ) )
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
	if ( FAILED( hr = D3DXCreateEffectFromFile( D3DDevice,
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
			OutputDebugStringA( ( char* ) pBuffer->GetBufferPointer() );
			SAFE_RELEASE( pBuffer );
		}

		return NULL;
	}

	return pEffect;
}
