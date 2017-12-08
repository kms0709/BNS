#pragma once

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
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

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


