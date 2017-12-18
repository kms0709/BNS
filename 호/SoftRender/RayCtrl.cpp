#include "stdafx.h"
#include "RayCtrl.h"

RayCtrl::RayCtrl()
	: direction(0.0f, 0.0f, 0.0f)
	, orgPosition(0.0f, 0.0f, 0.0f)
{
}

RayCtrl::~RayCtrl()
{
}

RayCtrl RayCtrl::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 viewPort;
	D3DDevice->GetViewport(&viewPort);

	D3DXMATRIXA16 matProjection;
	D3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

	RayCtrl r;
	r.direction.x = ((2.0f * x) / viewPort.Width - 1.0f) / matProjection._11;
	r.direction.y = ((-2.0f * y) / viewPort.Height + 1.0f) / matProjection._22;
	r.direction.z = 1.0f;

	return r;
}

RayCtrl RayCtrl::RayAtWorldSpace(int x, int y)
{
	RayCtrl r = RayCtrl::RayAtViewSpace(x, y);

	D3DXMATRIXA16 matView, matInvView;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.orgPosition, &r.orgPosition, &matInvView);
	D3DXVec3TransformNormal(&r.direction, &r.direction, &matInvView);
	D3DXVec3Normalize(&r.direction, &r.direction);

	return r;
}


bool RayCtrl::IsPicked(SphereInfo* sphereInfo)
{
	RayCtrl r = (*this);

	D3DXMATRIXA16 worldMat;
	D3DXMatrixIdentity(&worldMat);
	worldMat._41 = -sphereInfo->center.x;
	worldMat._42 = -sphereInfo->center.y;
	worldMat._43 = -sphereInfo->center.z;

	D3DXVec3TransformCoord(&r.orgPosition, &r.orgPosition, &worldMat);
	D3DXVec3TransformNormal(&r.direction, &r.direction, &worldMat);

	float vv = D3DXVec3Dot(&r.direction, &r.direction);
	float qv = D3DXVec3Dot(&r.orgPosition, &r.direction);
	float qq = D3DXVec3Dot(&r.orgPosition, &r.orgPosition);	
	float rr = sphereInfo->radi * sphereInfo->radi;

	if (qv * qv - vv * (qq - rr) >= 0) return true;
	else return false;
}
