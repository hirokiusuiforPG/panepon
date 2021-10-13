#pragma once

#include "DxLib.h"
#include "BaseObject.h"
#include "define.h"


class CTimeKeeper : public CBaseObject
{
	int Handle;		//�摜�n���h��
	
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