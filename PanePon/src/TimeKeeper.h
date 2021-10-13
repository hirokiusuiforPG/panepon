#pragma once

#include "DxLib.h"
#include "BaseObject.h"
#include "define.h"


class CTimeKeeper : public CBaseObject
{
	int Handle;		//‰æ‘œƒnƒ“ƒhƒ‹
	
	int Counter;

	bool flag;//update

	void FrameCnt();
	void FallBlock();
	void UpliftBlock();

public:
	CTimeKeeper();

	void Initialize(double time);
	void Finalize();
	void Update();
	void Draw();

	inline bool GetFlag() { return flag; }

	//inline CTimeKeeper *GetThisPtr() { return this; }
	//inline std::list<CEnemy> *GetEnemyPtr() { return &Enemy; }
};