#pragma once
#include "SingletonBase.h"


class ObjectManager : public SingletonBase<ObjectManager>
{
private:
	set<Object*> m_setObject;

public:
	void AddObject( Object* object );
	void RemoveObject( Object* object );
	void Destroy();


	ObjectManager();
	~ObjectManager();
};

