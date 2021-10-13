#pragma once

#include "DxLib.h"
#include "BaseObject.h"



class CMove
{
	//CBlockMgr	*BlockMgr;

	void HorChange();//左右に交換
	void Gravity();//updateから、ブロックを下に落とす。
	void Uplift();//

public:
	CMove();
	//void Initialize(CBlockMgr *e);
	void Update();
	void Draw();
};
