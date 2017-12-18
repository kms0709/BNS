#pragma once

#include "iMap.h"


class OBJMap : public iMap
{
protected:
	vector<D3DXVECTOR3> mapVertex;

public:
	OBJMap ( void );
	virtual ~OBJMap ( void );

	virtual void Load ( char* szFullPath, D3DXMATRIXA16* pmat ) override;
	virtual bool GetHeight ( IN const float& x, OUT float& y, IN const float& z ) override;
	virtual void Render() override;
};

