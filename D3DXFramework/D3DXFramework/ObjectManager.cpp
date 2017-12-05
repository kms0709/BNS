#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
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