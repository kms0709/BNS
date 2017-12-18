#pragma once

#define g_pAutoReleasePool AutoReleasePool::GetInstance()

class AutoReleasePool
{
	SINGLETON( AutoReleasePool );
private:
	list<Object*> objectList;

public:
	void AddObject( Object* object );
	void Drain();
};

