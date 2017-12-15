#pragma once

struct Bone;

class PlayerModel
{
private:

	SkinnedMesh* popori_body;
	SkinnedMesh* popori_head;
	SkinnedMesh* popori_tail;
	SkinnedMesh* weapon;

	int n;

	D3DXMATRIX matWorld;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	void SetMatWorld( D3DXMATRIX mat ) { matWorld = mat; }

	PlayerModel();
	~PlayerModel();
};

