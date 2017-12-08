#include "StdAfx.h"
#include "Object.h"


Object::Object( void )
	: refCount( 1 )
{
	g_pObjectManager->AddObject( this );
}

Object::~Object( void )
{
	g_pObjectManager->RemoveObject( this );
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
	g_pAutoReleasePool->AddObject( this );
}
