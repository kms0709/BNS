#pragma once

class cCube;

class LinearInterpolation : public Object
{
private:
	vector<VertexPC>	lineVerts;
	Cube*				cubeCtrl;

public:
	LinearInterpolation( void );
	virtual ~LinearInterpolation( void );

	void Init();
	void Update();
	void Render();
};

