#pragma once

struct Bone;

class SkinnedMesh
{
	friend class SkinnedMeshManager;


public:
	SkinnedMesh( wchar_t* szFolder, wchar_t* szFilename );
	~SkinnedMesh( void );

	void Update();
	void UpdatePivot();
	void AnimationUpdate();
	void Render();
	void SetAnimationIndex( int index, bool isBlend );

	void SetRandomTrackPosition(); // 테스트용

	inline void SetPosition( D3DXVECTOR3 v )
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
	}
	inline void SetRotation( D3DXVECTOR3 r )
	{
		m_fRot = r;
	}
	inline SphereInfo* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}

	void SetMatrices( IN D3DXMATRIX mat ) { rootMatrix = mat; }
	void SetMatWorld( IN D3DXMATRIX mat ) { matWorld = mat; }
	LPD3DXFRAME GetRoot() { return ( LPD3DXFRAME ) root; }
	void SetRoot( Bone* b ) { root = b; }

private:
	SkinnedMesh();

	void Load( const wchar_t* foldername, const wchar_t* filename );
	LPD3DXEFFECT LoadEffect( wchar_t* szFilename );
	void Update( Bone* frame, D3DXMATRIX* pmatParent );
	void Render( Bone* frame );
	void BoundingSphereDraw();

	void SetupBoneMatrixPtrs( LPD3DXFRAME );
//	void UpdateSkinnedMesh ( Bone* );
	
	void Destroy();

private:
	// 하나만 생성
	Bone*						root;
	D3DXMATRIX					rootMatrix;
	D3DXMATRIX					matWorld;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	SphereInfo					m_stBoundingSphere;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	animationController;
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_fRot;
	float						blendTime;
	float						passedBlendTime;


};
