#include "stdafx.h"
#include "Object.h"


Object::Object()
	: refCount( 1 )
{
	MANAGER_OBJECT->AddObject( this );
}


Object::~Object()
{
	MANAGER_OBJECT->RemoveObject( this );
	assert( refCount <= 0 && "Release�� �̿��ؼ� ��ü�� �����ϼ���." );
}

void Object::AddRef()
{
	++refCount;
}

void Object::Release()
{
	--refCount;
	if ( refCount <= 0 )
	{
		delete this;
	}
}

void Object::AutoRelease()
{
	AUTORELEASE->AddObject( this );
}
