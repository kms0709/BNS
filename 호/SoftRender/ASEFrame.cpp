#include "stdafx.h"
#include "ASEFrame.h"

ASEFrame::ASEFrame()
	: materialTexture(NULL)
{
	D3DXMatrixIdentity(&localTM);
	D3DXMatrixIdentity(&worldTM);
}

ASEFrame::~ASEFrame()
{
	SAFE_RELEASE(materialTexture);
}

void ASEFrame::init()
{
	D3DDevice->CreateVertexBuffer(
		PNTVerts.size() * sizeof(VertexPNT),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0);

	VertexPNT* verPNT;
	vertexBuffer->Lock(0, 0, (void**)&verPNT, 0);

	for (int i = 0; i < PNTVerts.size(); i++)
	{
		verPNT[i] = PNTVerts[i];
	}
	vertexBuffer->Unlock();

	if (!childList.empty())
	{
		for each(auto it in childList) 
		{
			SAFE_DELETE_ARRAY(it);
			}
	}


}

void ASEFrame::Update(int keyFrame, D3DXMATRIXA16* parent)
{
	D3DXMATRIXA16 matLocalT, matLocalR;
	CalcLocalTranslationMatrix(keyFrame, matLocalT);
	CalcLocalRotationMatrix(keyFrame, matLocalR);

	localTM = matLocalR * matLocalT;
	worldTM = localTM;

	if (parent) worldTM *= *parent;

	for each(auto it in childList)
	{
		it->Update(keyFrame, &worldTM);
	}
}

void ASEFrame::Render()
{
	if (materialTexture)
	{
		D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		D3DDevice->SetTransform(D3DTS_WORLD, &worldTM);
		D3DDevice->SetTexture(0, materialTexture->GetTexture());
		D3DDevice->SetMaterial(&materialTexture->GetMaterial());
		D3DDevice->SetFVF(VertexPNT::FVF);
		D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			PNTVerts.size() / 3,
			&PNTVerts[0],
			sizeof(VertexPNT));
	}


	if (!childList.empty())
	{
		for each(auto it in childList) it->Render();
	}
}

void ASEFrame::AddChild(ASEFrame * child)
{
	if (child == NULL) return;

	SAFE_ADDREF(child);

	childList.push_back(child);

}

void ASEFrame::Destroy()
{
	for each(auto it in childList)
	{
		it->Destroy();
	}
	Release();
}

void ASEFrame::CalcLocalTM(ASEFrame * pParent)
{
	localTM = worldTM;

	if (pParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, &pParent->GetWorldTM());
		localTM *= matInvParent;
	}

	for each (auto it in childList)
	{
		it->CalcLocalTM(this);
	}

}

void ASEFrame::CalcLocalTranslationMatrix(IN int nKeyFrame, OUT D3DXMATRIXA16 & mat)
{
	D3DXMatrixIdentity(&mat);
	if (posTrackList.empty())
	{
		mat._41 = localTM._41;
		mat._42 = localTM._42;
		mat._43 = localTM._43;
	}
	else if (nKeyFrame <= posTrackList.front().n)
	{
		mat._41 = posTrackList.front().v.x;
		mat._42 = posTrackList.front().v.y;
		mat._43 = posTrackList.front().v.z;
	}
	else if (nKeyFrame >= posTrackList.back().n)
	{
		mat._41 = posTrackList.back().v.x;
		mat._42 = posTrackList.back().v.y;
		mat._43 = posTrackList.back().v.z;
	}
	else
	{
		int nNext = -1;
		for (size_t i = 0; i < posTrackList.size(); ++i)
		{
			if (posTrackList[i].n > nKeyFrame)
			{
				nNext = i;
				break;
			}
		}
		int nPrev = nNext - 1;

		float t = (nKeyFrame - posTrackList[nPrev].n) /
			(float)(posTrackList[nNext].n - posTrackList[nPrev].n);

		D3DXVECTOR3 v;
		D3DXVec3Lerp(&v, &posTrackList[nPrev].v, &posTrackList[nNext].v, t);
		mat._41 = v.x;
		mat._42 = v.y;
		mat._43 = v.z;
	}
}

void ASEFrame::CalcLocalRotationMatrix(IN int nKeyFrame, OUT D3DXMATRIXA16 & mat)
{
	D3DXMatrixIdentity(&mat);
	if (rotTrackList.empty())
	{
		mat = localTM;
		mat._41 = 0.0f;
		mat._42 = 0.0f;
		mat._43 = 0.0f;
	}
	else if (nKeyFrame <= rotTrackList.front().n)
	{
		D3DXMatrixRotationQuaternion(&mat, &rotTrackList.front().q);
	}
	else if (nKeyFrame >= rotTrackList.back().n)
	{
		D3DXMatrixRotationQuaternion(&mat, &rotTrackList.back().q);
	}
	else
	{
		int nNext = -1;
		for (size_t i = 0; i < rotTrackList.size(); ++i)
		{
			if (rotTrackList[i].n > nKeyFrame)
			{
				nNext = i;
				break;
			}
		}
		int nPrev = nNext - 1;

		float t = (nKeyFrame - rotTrackList[nPrev].n) /
			(float)(rotTrackList[nNext].n - rotTrackList[nPrev].n);

		D3DXQUATERNION q;
		D3DXQuaternionSlerp(&q, &rotTrackList[nPrev].q, &rotTrackList[nNext].q, t);
		D3DXMatrixRotationQuaternion(&mat, &q);
	}
}
