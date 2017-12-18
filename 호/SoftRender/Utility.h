#pragma once

struct ASEScene
{
	int firstFrame;
	int lastFrame;
	int frameSpeed;
	int ticksPerFrame;

};

struct RotationSample
{
	int n;
	D3DXQUATERNION q;

};

struct PositionSample
{
	int n;
	D3DXVECTOR3 v;
};

struct SphereInfo
{
	bool isFrust;
	bool isPicked;

	float radi;

	D3DXVECTOR3 center;
};


struct VertexPC
{
	VertexPC(D3DXVECTOR3 _p, D3DCOLOR _c)
		: p(_p)
		, c(_c)
	{}

	VertexPC()
	{}

	D3DXVECTOR3 p;
	D3DCOLOR c;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct VertexPN
{
	VertexPN(D3DXVECTOR3 _p, D3DXVECTOR3 _n)
		: p(_p)
		, n(_n)
	{}

	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL, };

};



struct VertexPNT
{
	VertexPNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		: p(_p)
		, n(_n)
		, t(_t)
	{}

	VertexPNT()
	{}

	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };

};

struct VertexPT
{
	VertexPT(D3DXVECTOR3 _p, D3DXVECTOR2 _t)
		: p(_p)
		, t(_t)
	{}

	VertexPT()
	{}

	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct VertexRHWC
{
	VertexRHWC(D3DXVECTOR4 _p, D3DCOLOR _c)
		: p(_p)
		, c(_c)
	{}

	VertexRHWC()
	{}

	D3DXVECTOR4 p;
	D3DCOLOR c;

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_TEX1, };
};



#define SINGLETON( className ) private: \
className (); \
~className (); \
public: \
	static className* GetInstance () \
	{ \
		static className instance; \
		return &instance; \
	}


#define SAFE_RELEASE(p) if(p) {(p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) {delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete [] (p); (p) = NULL;}
#define SAFE_ADDREF(p) if(p) { (p)->AddRef(); }


#define GETSET(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void) const { return varName; }\
public: inline void set##funName(varType var){ varName = var; }

#define GETSET_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define GETSET_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
		SAFE_RELEASE(varName);\
		SAFE_ADDREF(var);\
		varName = var;\
	}\
}


