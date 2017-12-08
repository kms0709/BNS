#include "StdAfx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager( void )
{
}

ObjectManager::~ObjectManager( void )
{
}

void ObjectManager::AddObject( Object* object )
{
	m_setObject.insert( object );
}

void ObjectManager::RemoveObject( Object* object )
{
	m_setObject.erase( object );
}

void ObjectManager::Destroy()
{
	assert( m_setObject.empty() && "������ ��ü �� �������� ���� ��ü�� �ֽ��ϴ�." );
}
