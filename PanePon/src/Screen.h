#pragma once

#include "Cursor.h"
#include "BlockMgr.h"
#include "DeleteDecide.h"
#include "board.h" 

class CScreen
{
	CCursor			Cursor;
	CBlockMgr		BlockMgr;
	CDeleteDecide	DeleteDecide;

	int Handle;		//背景

	void CrossBlock();

public:
	CScreen();
	~CScreen();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();


	//inline CScreen *GetThisPtr() { return this; }

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//敵を倒した場合	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//画面上部までパネルが来た場合

	inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//時間切れ
};
