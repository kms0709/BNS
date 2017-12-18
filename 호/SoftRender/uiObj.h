#pragma once
class uiObj 
	//: public GameObject
{
public:
	uiObj();
	~uiObj();

	virtual void update();
	virtual void updateWorldTM();
	virtual void updateChildren();
	virtual void render( LPD3DXSPRITE sprite );
	virtual void addChild(uiObj*);
	virtual void destroy();
	virtual uiObj* getChildByTag( int _tag );


protected:
	GETSET(D3DXVECTOR3, localPos, LocalPos);
	GETSET(uiObj*, parent, Parent);
	GETSET(D3DXVECTOR2, size, Size);
	GETSET(bool, isDebugRender, DebugRender);
	GETSET(int, tag, Tag);

	vector<uiObj*> childList;
	D3DXMATRIXA16 worldMatrix;

};

