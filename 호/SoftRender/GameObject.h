#pragma once
#include "Object.h"

#include "Action.h"

class GameObject : public Object
{

public:
	GameObject( void );
	virtual ~GameObject( void );
	virtual void Update();
	virtual void Render();

protected:
	D3DXVECTOR3		prevPosition;

	GETSET ( Action*, action, Action );
	GETSET_REF(D3DXMATRIXA16, worldMat, worldMat);
	GETSET_REF(D3DXMATRIXA16, matS, matS);
	GETSET_REF(float, rotaY, rotaY);
	GETSET_REF(D3DXVECTOR3, direction, Direction);
	GETSET_REF(D3DXVECTOR3, position, Position);

};

