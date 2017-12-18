#include "stdafx.h"

#include "Matrix.h"
#include <iostream>
#include <iomanip>

#include "vector3.h"

Matrix::Matrix ( const int dimension )
{
	Row row;
	row.Resize ( dimension );

	for ( int i = 0; i < dimension; ++i ) {
		data.push_back ( row );
	}
	this->dimension = dimension;
}

Matrix::~Matrix ()
{
}

Matrix::Row & Matrix::operator[]( const int index )
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return data[index];
}

Matrix Matrix::operator+( Matrix & mat )
{
	Matrix result ( mat.GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			result[i][j] = ( *this )[i][j] + mat[i][j];
		}
	}
	return  result;
}

Matrix Matrix::operator-( Matrix & mat )
{
	Matrix result ( mat.GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			result[i][j] = ( *this )[i][j] - mat[i][j];
		}
	}
	return  result;
}

Matrix Matrix::operator*( const float scalar )
{
	Matrix result ( GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			result[i][j] = ( *this )[i][j] * scalar;
		}
	}
	return  result;

}

Matrix Matrix::operator*( Matrix & mat )
{
	Matrix result ( mat.GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			result[i][j] = 0;
			for ( int inner = 0; inner < dimension; ++inner )
				result[i][j] += ( *this )[i][inner] * mat[inner][j];
		}
	}
	return  result;

}

void Matrix::Random ()
{
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			( *this )[i][j] = rand () / ( RAND_MAX / 20.0f );
		}
	}
}

void Matrix::Print ()
{
	for ( int i = 0; i < dimension; ++i ) {
		std::cout << std::setiosflags ( std::ios::fixed ) << std::setw ( 6 ) << std::setprecision ( 02 );
		for ( int j = 0; j < dimension; ++j ) {
			std::cout << ( *this )[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::Transpose ()
{
	Matrix result ( GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			result[j][i] = ( *this )[i][j];
		}
	}
	return  result;

}

Matrix Matrix::Identity ( const int dimension )
{

	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			( *this )[i][j] = ( ( i == j ) ? 1.0f : 0.0f );
		}
	}
	return ( *this );
}

bool Matrix::Inverse ( OUT float & determinent, OUT Matrix & outMatrix )
{

	outMatrix.Identity ( 4 );
	//inv = 1 / det(A) * adj(A)
	determinent = Determinent ();

	if ( fabs ( determinent ) <= 0.0001f )
		return false;

	outMatrix = Adjoint () * ( 1 / determinent );

	return false;
}


float Matrix::Determinent ()
{

	if ( GetDimesion () == 2 ) {
		return ( ( *this )[0][0] * ( *this )[1][1] ) - ( ( *this )[0][1] * ( *this )[1][0] );
	}

	// sigma ( i = 0 ~ N) a(i,j) * C(i,j)
	float determinent = 0;
	for ( int i = 0; i < GetDimesion (); ++i ) {
		determinent += ( *this )[i][0] * Cofactor ( i, 0 );
	}
	return determinent;

}

float Matrix::Cofactor ( int row, int col )
{
	// A(i,j) = -1^(i+j) * Miner(i,j);
	float  Const = ( ( ( ( row + col ) % 2 == 0 ) ? 1.0f : -1.0f ) );
	return Const * Miner ( row, col );
}

float Matrix::Miner ( int row, int col )
{
	int minerRow = 0;
	int minerCol = 0;

	Matrix mat ( GetDimesion () - 1 );
	//mat.Identity ( GetDimesion () - 1 );
	for ( int i = 0; i < GetDimesion (); ++i ) {
		if ( i == row ) continue;
		minerCol = 0;
		for ( int j = 0; j < GetDimesion (); ++j ) {
			if ( j == col ) continue;
			mat[minerRow][minerCol] = ( ( *this )[i][j] );
			++minerCol;
		}
		++minerRow;
	}

	return mat.Determinent ();
}


Matrix Matrix::Adjoint ()
{
	Matrix mat ( GetDimesion () );
	for ( int i = 0; i < dimension; ++i ) {
		for ( int j = 0; j < dimension; ++j ) {
			mat[i][j] = Cofactor ( j, i );
		}
	}
	return mat;
}


Matrix Matrix::Translation ( float x, float y, float z )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );

	mat[3][0] = x;
	mat[3][1] = y;
	mat[3][2] = z;

	return mat;
}

Matrix Matrix::Translation ( Vector3 & v )
{
	return Translation ( v.x, v.y, v.z );
}

Matrix Matrix::RotateX ( float Angle )
{
	Matrix mat(4);
	mat.Identity (4);
	mat[1][1] = cosf ( Angle );
	mat[1][2] = sinf ( Angle );
	mat[2][1] = -sinf ( Angle );
	mat[2][2] = cosf ( Angle );

	return mat;
}

Matrix Matrix::RotateY ( float Angle )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );
	mat[0][0] = cosf ( Angle );
	mat[0][2] = -sinf ( Angle );
	mat[2][0] = sinf ( Angle );
	mat[2][2] = cosf ( Angle );

	return mat;
}

Matrix Matrix::RotateZ ( float Angle )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );
	mat[0][0] = cosf ( Angle );
	mat[0][1] = sinf ( Angle );
	mat[1][0] = -sinf ( Angle );
	mat[1][1] = cosf ( Angle );

	return mat;
}

Matrix Matrix::Scale ( float x, float y, float z )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;	

	return mat;

}

Matrix Matrix::View ( Vector3 * pEye, Vector3 * pUp, Vector3 * pLookAt )
{
	Vector3 l;
	Vector3 r;
	Vector3 u;

	l = ( *pLookAt - *pEye ).Normalize ();
	r = Vector3::Cross ( *pUp, l ).Normalize ();
	u = Vector3::Cross ( l, r ).Normalize ();

	Matrix mat ( 4 );
	mat.Identity ( 4 );

	mat[0][0] = r.x; mat[0][1] = u.x; mat[0][2] = l.x;
	mat[1][0] = r.y; mat[1][1] = u.y; mat[1][2] = l.y;
	mat[2][0] = r.z; mat[2][1] = u.z; mat[2][2] = l.z;

	mat[3][0] = -Vector3::Dot ( r, *pEye );
	mat[3][1] = -Vector3::Dot ( u, *pEye );
	mat[3][2] = -Vector3::Dot ( l, *pEye );

	return mat;
}

Matrix Matrix::Projection ( float fFovY, float fAspect, float fNearZ, float fFarZ )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );

	float fScaleY = 1.0f / tanf ( fFovY / 2.0f );
	float fScaleX = fScaleY / fAspect;


	mat[0][0] = fScaleX;
	mat[1][1] = fScaleY;
	mat[2][2] = fFarZ / (fFarZ - fNearZ);
	mat[2][3] = 1.0f;
	mat[3][2] = -( fFarZ * fNearZ ) / ( fFarZ - fNearZ );
	mat[3][3] = 0.0f;

	return mat;
}

Matrix Matrix::Viewport ( float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ )
{
	Matrix mat ( 4 );
	mat.Identity ( 4 );

	mat[0][0] = fW / 2.0f;
	mat[1][1] = -fH / 2.0f;
	mat[2][2] = fMaxZ - fMinZ;
	mat[3][0] = fX + fW / 2.0f;
	mat[3][1] = fY + fH / 2.0f;
	mat[3][2] = fMinZ;


	return mat;
}












