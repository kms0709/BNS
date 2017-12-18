#pragma once



class Matrix;

class Vector3
{


public:
	Vector3 ();
	Vector3 ( float _x, float _y, float _z );
	~Vector3 ();

public:
	float x, y, z;

	bool operator == ( Vector3& v );
	bool operator != ( Vector3& v );
	Vector3 operator + ( Vector3& v );
	Vector3 operator - ( Vector3& v );
	Vector3 operator * ( float f );

	float Length ();
	float LengthSq (); // ±æÀÌ Á¦°ö
	Vector3 Normalize ();
	static float Dot ( Vector3& v1, Vector3& v2 );
	static Vector3 Cross ( Vector3& v1, Vector3& v2 );
	Vector3 TransformCoord ( Matrix& pmat ); // Æ÷ÀÎÆ®
	Vector3 TransformNormal ( Matrix& pmat ); // º¤ÅÍ


};

