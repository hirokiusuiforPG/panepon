#pragma once

class CBaseObject
{
protected:
	double x, y;	//���W
public:
	CBaseObject();
	virtual ~CBaseObject();

	virtual void Initialize();

	double GetX(){ return x; }
	double GetY(){ return y; }
};