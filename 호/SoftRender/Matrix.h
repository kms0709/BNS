#pragma once

#include <vector>
#define OUT

class Vector3;

class Matrix
{
private:
	class Row {
		std::vector<float> rowData;
	public:
		void Resize ( int size ) {
			rowData.resize ( size );
		}
		float& operator[] ( int index ) {
			return rowData[index];
		}
	};

public:
	Matrix ( const int dimension );
	~Matrix ();
	const int GetDimesion () { return dimension; }


	Row& operator[] ( const int index );
	Matrix operator+( Matrix& mat );
	Matrix operator-( Matrix& mat );
	Matrix operator*( const float scalar );
	Matrix operator*( Matrix& mat );

	void Random ();
	void Print ();
	bool Inverse ( OUT float& determinent, OUT Matrix& outMatrix );
	Matrix Transpose ();
	Matrix Identity ( const int dimension );

	float Determinent ();
	Matrix Adjoint ();
	float Cofactor ( int row, int col );
	float Miner ( int row, int col );

	//두번째 추가

	static	Matrix Translation ( float x, float y, float z );
	static	Matrix Translation ( Vector3& v );
	static	Matrix RotateX ( float Angle );
	static	Matrix RotateY ( float Angle );
	static	Matrix RotateZ ( float Angle );
	static	Matrix Scale ( float x, float y, float z );

	static	Matrix	View ( Vector3* pEye/* 0, 0, -5 */, Vector3* pUp/* 0, 1, 0 */, Vector3* pLookAt /* 0, 0, 0 */ );
	static	Matrix Projection ( float fFovY /* 45도 */, float fAspect, float fNearZ /* 1 */, float fFarZ /* 1000 */ );
	static	Matrix Viewport ( float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ );





private:
	std::vector<Row> data;
	int dimension;

};





