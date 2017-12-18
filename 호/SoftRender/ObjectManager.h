#pragma once

#define g_pObjectManager ObjectManager::GetInstance()

class ObjectManager
{
	SINGLETON( ObjectManager );
private:
	// 유무 체크할때 쓰는거
	set<Object*> m_setObject;

public:
	void AddObject( Object* object );
	void RemoveObject( Object* object );
	void Destroy();
};

