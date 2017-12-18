#include "stdafx.h"
#include "FrustumCulling.h"

FrustumCulling::FrustumCulling()
{
	_vWorldVtx.clear();

	_vWorldVtx.push_back(D3DXVECTOR3( -1,  1, 1));
	_vWorldVtx.push_back(D3DXVECTOR3(  1,  1, 1));
	_vWorldVtx.push_back(D3DXVECTOR3( -1,  1, 0));
	_vWorldVtx.push_back(D3DXVECTOR3(  1,  1, 0));
	_vWorldVtx.push_back(D3DXVECTOR3( -1, -1, 1));
	_vWorldVtx.push_back(D3DXVECTOR3(  1, -1, 1));
	_vWorldVtx.push_back(D3DXVECTOR3( -1, -1, 0));
	_vWorldVtx.push_back(D3DXVECTOR3(  1, -1, 0));

	_vPlane.resize(6);
}

FrustumCulling::~FrustumCulling()
{
}

bool FrustumCulling::IsFrustum(SphereInfo* tSphereInfo)
{
	for each(D3DXPLANE it in _vPlane)
	{
		if (D3DXPlaneDotCoord(&it, &tSphereInfo->center) > tSphereInfo->radi)
		{
			tSphereInfo->isFrust = false;
			return false;
		}
	}

	tSphereInfo->isFrust = true;
	return true;
}

void FrustumCulling::Update()
{
	vector<D3DXVECTOR3> worldVec(8);

	D3DXMATRIX viewMat, proMat;

	D3DDevice->GetTransform(D3DTS_VIEW, &viewMat);
	D3DDevice->GetTransform(D3DTS_PROJECTION, &proMat);

	for (int i = 0; i < worldVec.size(); ++i)
	{
		D3DXVec3Unproject(&worldVec[i], &_vWorldVtx[i], nullptr, &proMat, &viewMat, nullptr);
	}

	D3DXPlaneFromPoints(&_vPlane[0], &worldVec[0], &worldVec[2], &worldVec[4]);

	D3DXPlaneFromPoints(&_vPlane[1], &worldVec[3], &worldVec[1], &worldVec[7]);

	D3DXPlaneFromPoints(&_vPlane[2], &worldVec[0], &worldVec[1], &worldVec[2]);

	D3DXPlaneFromPoints(&_vPlane[3], &worldVec[6], &worldVec[7], &worldVec[4]);

	D3DXPlaneFromPoints(&_vPlane[4], &worldVec[2], &worldVec[3], &worldVec[7]);

	D3DXPlaneFromPoints(&_vPlane[5], &worldVec[1], &worldVec[0], &worldVec[5]);
}
