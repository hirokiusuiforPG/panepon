#pragma once

#include "DxLib.h"
#include "../src/BaseObject.h"

class CTestBlock : public CBaseObject
{
	double x, y, kind, exist = 0, flag = 0, rekind = 0;

public:
	CTestBlock();

	void Initialize(double x, double y);
	void Update();
	void Draw(int handle);

};