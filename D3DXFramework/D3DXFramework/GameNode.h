#pragma once
class GameNode
{
private:

	bool _managerInit;

public:
	virtual HRESULT Init( void );
	virtual HRESULT Init( bool managerInit );
	virtual void Release( void );
	virtual void Update( void );
	virtual void Render( void );

	////�������̽�
	//virtual void move(void) = 0;	//���������Լ�
	//virtual void jump(void) = 0;
	//virtual void attack(void) = 0;


	LRESULT MainProc( HWND, UINT, WPARAM, LPARAM );


	GameNode();
	virtual ~GameNode();
};

