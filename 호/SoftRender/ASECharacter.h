#pragma once
#include "ASEFrame.h"

class ASEFrame;
class HeightMap;

class ASECharacter : public Object
{
public:
	ASECharacter ();
	~ASECharacter ();

	void Load ( char* filename );
	void Update(HeightMap* map);
	void Render ();

	D3DXVECTOR3 getPosition() { return _position; }


protected:

	GETSET(float, rotationY, rotationY);

	D3DXMATRIXA16 worldMatrix;

	ASEScene aseScene;
	ASEFrame* root;

	D3DXVECTOR3 _position;

	int firstTick, lastTick, tickSpeed, keyFrame;

};

