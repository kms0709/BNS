#pragma once
class UIManager : public iUIButtonDelegate
{
private:
	uiObj* _uiRoot;
	LPD3DXSPRITE _sprite;

public:
	UIManager();
	~UIManager();

	void init();
	void update();
	void render();

	virtual void OnClick(uiButton* pSender);




	////			�ؽ�Ʈ = FLASE �̹��� = TRUE? ������ ���� �̸�
	//HRESULT init(BOOL image, string fileName);
	////			�ؽ�Ʈ = FLASE �̹��� = TRUE? ������ ���� �̸�  ��ġ
	//HRESULT init(BOOL image, string fileName, D3DXVECTOR3 vec);
	////			�ؽ�Ʈ = FLASE �̹��� = TRUE? ������ ���� �̸�  ��ġ
	//HRESULT init(BOOL image, string fileName, float x, float y, float z);
};

