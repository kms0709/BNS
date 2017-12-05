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

	////인터페이스
	//virtual void move(void) = 0;	//순수가상함수
	//virtual void jump(void) = 0;
	//virtual void attack(void) = 0;


	LRESULT MainProc( HWND, UINT, WPARAM, LPARAM );


	GameNode();
	virtual ~GameNode();
};

