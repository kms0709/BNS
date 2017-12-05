#include "stdafx.h"
#include "TestScene2.h"


TestScene2::TestScene2()
{
}


TestScene2::~TestScene2()
{
}

HRESULT TestScene2::Init()
{
	SkinnedMesh* _skinnedMesh = new SkinnedMesh( L"./data/test/lakan_new", L"lakan.X" );
	_skinnedMesh->SetPosition( D3DXVECTOR3( 0, 0, 0 ) );
	_SMList.push_back( _skinnedMesh );

	return S_OK;
}

void TestScene2::Release()
{
	for each ( auto p in _SMList )
	{
		SAFE_DELETE( p );
	}
	_SMList.clear();
}

void TestScene2::Update()
{
}

void TestScene2::Render()
{
	for ( int i = 0; i < _SMList.size(); ++i )
	{
		_SMList[ i ]->UpdateAndRender();
	}

}