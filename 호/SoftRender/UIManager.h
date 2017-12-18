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




	////			텍스트 = FLASE 이미지 = TRUE? 생성할 파일 이름
	//HRESULT init(BOOL image, string fileName);
	////			텍스트 = FLASE 이미지 = TRUE? 생성할 파일 이름  위치
	//HRESULT init(BOOL image, string fileName, D3DXVECTOR3 vec);
	////			텍스트 = FLASE 이미지 = TRUE? 생성할 파일 이름  위치
	//HRESULT init(BOOL image, string fileName, float x, float y, float z);
};

