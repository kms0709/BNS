#pragma once
#include "GameNode.h"
#include "TestScene.h"
#include "TestScene2.h"

class MainGame : public GameNode
{
private:



public:
	virtual HRESULT Init( void );
	virtual void Release( void );
	virtual void Update( void );
	virtual void Render( void );




	MainGame();
	~MainGame();
};

