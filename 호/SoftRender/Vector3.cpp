#include "stdafx.h"

#include "Vector3.h"

#include "Matrix.h"

Vector3::Vector3 ()
{
}

Vector3::Vector3 ( float _x, float _y, float _z )
{
	x = _x;
	y = _y;
	z = _z;
}


Vector3::~Vector3 ()
{
}

bool Vector3::operator==( Vector3 & v )
{
	if ( fabs ( ( *this ).x - v.x ) > 0.0002f ) return false;
	if ( fabs ( ( *this ).y - v.y ) > 0.0002f ) return false;
	if ( fabs ( ( *this ).z - v.z ) > 0.0002f ) return false;

	return true;
}

bool Vector3::operator!=( Vector3 & v )
{
	return !( ( *this ) == v );
}

Vector3 Vector3::operator+( Vector3 & v )
{
	return Vector3 ( x + v.x, y + v.y, z + v.z );
}

Vector3 Vector3::operator-( Vector3 & v )
{
	return Vector3 ( x - v.x, y - v.y, z - v.z );
}

Vector3 Vector3::operator*( float f )
{
	return Vector3 ( x * f, y * f, z * f );
}

float Vector3::Length ()
{
	return sqrt ( LengthSq () );
}

float Vector3::LengthSq ()
{
	return x*x + y*y + z*z;
}

Vector3 Vector3::Normalize ()
{
	float length = Length ();
	return Vector3 ( x / length, y / length, z / length );
}

float Vector3::Dot ( Vector3 & v1, Vector3 & v2 )
{
	// ÆÑÅÍº° °ö¼ÀÀÇ ÇÕ
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross ( Vector3 & v1, Vector3 & v2 )
{
	// A X B = ( a2 b3 - a3 b2 ) i , - (a1 * b3 - a3 b1) i, (a1 b2 - a2b1) k

	return Vector3 ( ( v1.y * v2.z - v1.z * v2.y ),
					 ( v1.z * v2.x - v1.x * v2.z ),
					 ( v1.x * v2.y - v1.y * v2.x ) );
}

Vector3 Vector3::TransformCoord ( Matrix& mat )
{
	Vector3 v1;
	v1.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0] + 1.0f * mat[3][0];
	v1.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1] + 1.0f * mat[3][1];
	v1.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2] + 1.0f * mat[3][2];
	float w = x * mat[0][3] + y * mat[1][3] + z * mat[2][3] + 1.0f * mat[3][3];
	if ( fabs ( w ) > 0.0001f )
	{
		v1.x /= w;
		v1.y /= w;
		v1.z /= w;
	}
	return v1;
}

Vector3 Vector3::TransformNormal ( Matrix& mat )
{
	Vector3 v1;
	v1.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0];
	v1.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1];
	v1.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2];
	return v1;

	return Vector3 ();
}
