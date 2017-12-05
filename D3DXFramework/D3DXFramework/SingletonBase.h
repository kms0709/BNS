#pragma once

template <typename T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	SingletonBase( void ) {};
	~SingletonBase( void ) {};

public:
	//�̱��� ������
	static T* GetSingleton( void );
	//�̱��� ���� �Լ�
	void ReleaseSingleton( void );
};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleton = 0;

//�̱��� �ҷ����� �Լ�
template <typename T>
T* SingletonBase<T>::GetSingleton( void )
{
	//���࿡ �̱����� ���ٸ� -> �̱��� ����
	if ( !singleton ) singleton = new T;

	//�׸��� ��ȯ
	return singleton;
}

//�̱��� �޸� ����
template <typename T>
void SingletonBase<T>::ReleaseSingleton( void )
{
	if ( singleton )
	{
		delete singleton;

		singleton = 0;
	}
}