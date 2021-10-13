#pragma once

#include "BaseObject.h"
#include "DxLib.h"
#include "../extra/DxAnimation.h"

class CEffect : public CBaseObject
{
protected:
	static DxGraphic Exprode;
	DxAnimation ExprodeAnime;
	bool ExAnimeFlag;


public:
	CEffect();
	~CEffect();

	void Initialize();
	void Update();

};