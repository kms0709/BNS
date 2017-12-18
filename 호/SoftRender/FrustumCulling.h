#pragma once
class FrustumCulling
{
private:
	vector<D3DXPLANE> _vPlane;
	vector<D3DXVECTOR3> _vWorldVtx;

public:
	FrustumCulling();
	~FrustumCulling();

	bool IsFrustum(SphereInfo* tSphereInfo);
	void Update();
};