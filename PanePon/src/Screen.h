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

	int Handle;		//”wŒi

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
	//“G‚ğ“|‚µ‚½ê‡	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//‰æ–Êã•”‚Ü‚Åƒpƒlƒ‹‚ª—ˆ‚½ê‡

	inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//ŠÔØ‚ê
};
