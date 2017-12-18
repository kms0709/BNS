#pragma once

class CharacterCtrl
{
public:
	CharacterCtrl ();
	~CharacterCtrl ();

	void Update(OBJMap* map);
	
	D3DXVECTOR3* GetPosition ();
	D3DXMATRIXA16* GetWorldTM ();
	
	float* getRoteY() { return &rotationY; }

private:
	D3DXVECTOR3 positionVector;
	D3DXMATRIXA16 worldMatrix;
	float rotationY;
	float speed;

	

};

