#pragma once

// 선 구조체
struct LinePC
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	LinePC() {}
	LinePC( D3DXVECTOR3 _p, D3DCOLOR _c )
		: p( _p ), c( _c )
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

// pointer, normal, texture
struct VertexPNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	VertexPNT() {}
	VertexPNT( D3DXVECTOR3 _p, D3DXVECTOR3 _t, D3DXVECTOR3 _n = D3DXVECTOR3( 0, 0, 0 ) )
		: p( _p ), n( _n ), t( _t )
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

// 원 정보
struct SphereInfo
{
	bool		isInFrustum;
	bool		isPicked;
	float		fRadius;
	D3DXVECTOR3 vCenter;
};

//==================================
// 매크로 함수 ##
//==================================

#define SAFE_RELEASE(p) if(p) {(p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) {delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete [] (p); (p) = NULL;}
#define SAFE_ADDREF(p) if(p) { (p)->AddRef(); }

// 일반 변수 가져올때
#define GETSET(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

// 변수의 주소값을 가져올때
#define GETSET_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

// 변수의 AddRef() 라는 함수를 불러옴 
#define GETSET_ADD_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
		SAFE_RELEASE(varName);\
		SAFE_ADDREF(var);\
		varName = var;\
	}\
}