#pragma once

template <typename T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase( void ) {};
	~SingletonBase( void ) {};

public:
	//싱글톤 접근자
	static T* GetSingleton( void );
	//싱글톤 해제 함수
	void ReleaseSingleton( void );
};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

//싱글톤 불러오는 함수
template <typename T>
T* SingletonBase<T>::GetSingleton( void )
{
	//만약에 싱글톤이 없다면 -> 싱글톤 생성
	if ( !singleton ) singleton = new T;

	//그리고 반환
	return singleton;
}

//싱글톤 메모리 해제
template <typename T>
void SingletonBase<T>::ReleaseSingleton( void )
{
	if ( singleton )
	{
		delete singleton;

		singleton = 0;
	}
}