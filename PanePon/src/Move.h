#pragma once

#include "DxLib.h"
#include "BaseObject.h"



class CMove
{
	//CBlockMgr	*BlockMgr;

	void HorChange();//���E�Ɍ���
	void Gravity();//update����A�u���b�N�����ɗ��Ƃ��B
	void Uplift();//

public:
	CMove();
	//void Initialize(CBlockMgr *e);
	void Update();
	void Draw();
};
