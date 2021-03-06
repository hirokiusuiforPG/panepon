#pragma once

#include "TimeKeeper.h"
#include "board.h" 

class CRule
{
	CTimeKeeper		TimeKeeper;

	int Handle;		//背景

public:
	CRule();
	~CRule();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//敵を倒した場合	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//画面上部までパネルが来た場合

	inline bool CheckGameEnd() { return TimeKeeper.GetFlag(); }
	//時間切れ
};
