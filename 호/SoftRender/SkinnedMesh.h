#pragma once

struct Bone;

class SkinnedMesh
{
	friend class SkinnedMeshManager;


public:
	SkinnedMesh ( char* szFolder, char* szFilename );
	~SkinnedMesh ( void );

	void UpdateAndRender ();
	void SetAnimationIndex ( int nIndex );

	void SetRandomTrackPosition (); // 테스트용

	inline void SetPosition ( D3DXVECTOR3 v )
	{
		m_vPosition = v;
		m_stBoundingSphere.center = v;
	}

	inline D3DXVECTOR3 GetPosition() { return m_vPosition; }

	inline void setScale(float ratio)
	{
		D3DXMatrixScaling(&sMat, ratio, ratio, ratio);
	}

	inline void setRotaY(float angle)
	{
		_rotaY = angle;
	}

	inline float getRotaY() { return _rotaY; }

	inline void setBodyMatrix(D3DXMATRIX bodyMat)
	{
		body = bodyMat;
	}

	inline SphereInfo* GetBoundingSphere ()
	{
		return &m_stBoundingSphere;
	}

	bool getAniEnd(int index);
	void setAniStop(bool stop) { _stop = stop; }

	void getMatrix(SkinnedMesh*, LPD3DXFRAME, LPCSTR);

private:
	SkinnedMesh ();	

	void Load ( const char* foldername, const char* filename );
	LPD3DXEFFECT LoadEffect ( char* szFilename );
	void Update ( Bone* frame, D3DXMATRIX* pmatParent );
	void Render ( Bone* frame );
	void SetupBoneMatrixPtrs ( LPD3DXFRAME );

	//void UpdateSkinnedMesh ( LPD3DXFRAME );	
	void Destroy ();

	float _rotaY;
private: 
	// 하나만 생성
	Bone*						root;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;

	D3DXMATRIX					sMat;
	D3DXMATRIX					_ryMat;
	D3DXMATRIX					tMat;



	D3DXMATRIX					body;
	LPD3DXEFFECT				m_pEffect;
	SphereInfo					m_stBoundingSphere;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	animationController;
	D3DXVECTOR3					m_vPosition;
	//float						blendTime;
	//float						passedBlendTime;

	float currentTime;

	bool _start;
	bool _stop;
};










