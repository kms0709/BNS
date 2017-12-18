#pragma once

class MaterialTexture;

struct Bone : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};

struct BoneMesh : public D3DXMESHCONTAINER
{
	//std::vector<MaterialTexture*>	materialTextureList;
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
	std::vector<D3DMATERIAL9>		vecMaterial;


	LPD3DXMESH				orgMesh;				// ���� �޽�
	LPD3DXMESH				workMesh;				// �۾� �޽� CloneMeshFVF�� ����
	D3DXMATRIX**			ppBoneMatrixPtrs;		// �� �޽��� ������ �ִ� ������'��'�� �����Ʈ���� ������ �迭
	D3DXMATRIX*				pBoneOffsetMatrices;	// ���� �޽��� ���ý����̽��� ������ ��Ʈ������.
	//D3DXMATRIX*				pCurrentBoneMatrices;	// �� ���� ���� �����Ʈ����


	DWORD					dwNumPaletteEntries;
	DWORD					dwMaxNumFaceInfls;
	DWORD					dwNumAttrGroups;
	LPD3DXBUFFER			pBufBoneCombos;

};



class AllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	AllocateHierarchy ();
	~AllocateHierarchy ();

	GETSET ( std::string, folder, Folder );
	GETSET ( D3DXVECTOR3, minVector, MinVector );
	GETSET ( D3DXVECTOR3, maxVector, MaxVector );
	GETSET ( DWORD, defaultPaletteSize, DefaultPaletteSize );
	GETSET ( DWORD, maxPaletteSize, MaxPaletteSize );


	// ID3DXAllocateHierarchy

	//------------------------------------------------------------------------
	// CreateFrame:
	// ------------
	// Requests allocation of a frame object.
	//
	// Parameters:
	//  Name
	//		Name of the frame to be created
	//	ppNewFrame
	//		Returns the created frame object
	//
	//------------------------------------------------------------------------
	STDMETHOD ( CreateFrame )( THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame ) override;

	//------------------------------------------------------------------------
	// CreateMeshContainer:
	// --------------------
	// Requests allocation of a mesh container object.
	//
	// Parameters:
	//  Name
	//		Name of the mesh
	//	pMesh
	//		Pointer to the mesh object if basic polygon data found
	//	pPMesh
	//		Pointer to the progressive mesh object if progressive mesh data found
	//	pPatchMesh
	//		Pointer to the patch mesh object if patch data found
	//	pMaterials
	//		Array of materials used in the mesh
	//	pEffectInstances
	//		Array of effect instances used in the mesh
	//	NumMaterials
	//		Num elements in the pMaterials array
	//	pAdjacency
	//		Adjacency array for the mesh
	//	pSkinInfo
	//		Pointer to the skininfo object if the mesh is skinned
	//	pBoneNames
	//		Array of names, one for each bone in the skinned mesh. 
	//		The numberof bones can be found from the pSkinMesh object
	//	pBoneOffsetMatrices
	//		Array of matrices, one for each bone in the skinned mesh.
	//
	//------------------------------------------------------------------------
	STDMETHOD ( CreateMeshContainer )( THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer ) override;

	//------------------------------------------------------------------------
	// DestroyFrame:
	// -------------
	// Requests de-allocation of a frame object.
	//
	// Parameters:
	//  pFrameToFree
	//		Pointer to the frame to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD ( DestroyFrame )( THIS_ LPD3DXFRAME pFrameToFree ) override;

	//------------------------------------------------------------------------
	// DestroyMeshContainer:
	// ---------------------
	// Requests de-allocation of a mesh container object.
	//
	// Parameters:
	//  pMeshContainerToFree
	//		Pointer to the mesh container object to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD ( DestroyMeshContainer )( THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree ) override;

};

