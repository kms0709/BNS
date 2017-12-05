#pragma once
#include "SingletonBase.h"


class AutoReleasePool : public SingletonBase<AutoReleasePool>
{
private:
	list<Object*> objectList;

public:
	void AddObject( Object* object );
	void Drain();


	AutoReleasePool();
	~AutoReleasePool();
};

