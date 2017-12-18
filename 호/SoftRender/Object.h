#pragma once

class Object
{
protected:
	IDirect3DVertexBuffer9* vertexBuffer;

private:
	int refCount;

public:
	Object( void );
	virtual ~Object( void );

	virtual void AddRef();
	virtual void Release();
	virtual void AutoRelease();
};

