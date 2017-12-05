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
	assert( refCount <= 0 && "Release를 이용해서 객체를 해제하세요." );
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
