#pragma once

struct Bone;

class SkinnedMesh
{
	friend class SkinnedMeshManager;


public:
	SkinnedMesh( wchar_t* szFolder, wchar_t* szFilename );
	~SkinnedMesh( void );

	void UpdateAndRender();
	void SetAnimationIndex( int nIndex );

	void SetRandomTrackPosition(); // �׽�Ʈ��

	inline void SetPosition( D3DXVECTOR3 v )
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
	}
	inline SphereInfo* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}

private:
	SkinnedMesh();

	void Load( const wchar_t* foldername, const wchar_t* filename );
	LPD3DXEFFECT LoadEffect( wchar_t* szFilename );
	void Update( Bone* frame, D3DXMATRIX* pmatParent );
	void Render( Bone* frame );
	void SetupBoneMatrixPtrs( LPD3DXFRAME );

	//void UpdateSkinnedMesh ( LPD3DXFRAME );	
	void Destroy();


private:
	// �ϳ��� ����
	Bone*						root;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	SphereInfo					m_stBoundingSphere;

	// ��ü���� ����
	LPD3DXANIMATIONCONTROLLER	animationController;
	D3DXVECTOR3					m_vPosition;
	//float						blendTime;
	//float						passedBlendTime;


};
