#include "stdafx.h"
#include "ASECharacter.h"

#include "ASEFrame.h"
#include "ASELoader.h"
#include "HeightMap.h"




ASECharacter::ASECharacter(void)
	: root(NULL)

{
	_position = { 1.0f, 0.0f, 1.0f };
	firstTick = lastTick = tickSpeed = keyFrame = 0;
	rotationY = 0.0f;

	D3DXMatrixIsIdentity(&worldMatrix);

}



ASECharacter::~ASECharacter(void)
{

	root->Destroy();

}



void ASECharacter::Load(char* szFullPath)
{

	ASELoader* aseLoader = new ASELoader;

	root = aseLoader->Load(szFullPath, &aseScene);

	root->init();


	root->AddRef();
	
	
	SAFE_RELEASE(aseLoader);

}



void ASECharacter::Update(HeightMap* map)
{
	D3DXVECTOR3 tempPosition = _position;

	firstTick = aseScene.firstFrame * aseScene.ticksPerFrame;
	
	lastTick = aseScene.lastFrame * aseScene.ticksPerFrame;
	
	tickSpeed = aseScene.frameSpeed * aseScene.ticksPerFrame;
	
	keyFrame = ((int)((tickSpeed / 1000.f) * TIMEMANAGER->getElapsedTime()) % (lastTick - firstTick) + firstTick);

	if (GetKeyState('A') & 0x8000) rotationY -= 0.1f;
	if (GetKeyState('D') & 0x8000) rotationY += 0.1f;


	D3DXVECTOR3 vDire = { 0, 0, 1 };
	D3DXMATRIXA16 matRotaY;
	D3DXMatrixIdentity(&matRotaY);

	D3DXMatrixRotationY(&matRotaY, rotationY);
	D3DXVec3TransformNormal(&vDire, &vDire, &matRotaY);

	if (GetKeyState('W') & 0x8000) tempPosition = tempPosition - vDire * 0.05f;
	if (GetKeyState('S') & 0x8000) tempPosition = tempPosition + vDire * 0.05f;

	if (map->GetHeight(tempPosition.x, tempPosition.y, tempPosition.z))
	{
		_position = tempPosition;
	}

	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	worldMatrix = matRotaY * trans;



	if (root)
	{
		root->Update(keyFrame, &worldMatrix);
	}

}


void ASECharacter::Render()
{
	if (root) root->Render();

}