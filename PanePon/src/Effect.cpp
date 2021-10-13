#include "Effect.h"

DxGraphic CEffect::Exprode = DxGraphic();
CEffect::CEffect()
{
	if (Exprode.GetNumber() == 0)
	{
		Exprode.LoadDiv("dat/img/pipo-btleffect144.png", 15, 1, 15, 640, 480);
	}
	ExAnimeFlag = false;
	ExprodeAnime.SetGraphic(&Exprode);
	ExprodeAnime.SetNextStep(5);
	ExprodeAnime.SetRepeatFlag(false);

}

CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
}

void CEffect::Update()
{
}
