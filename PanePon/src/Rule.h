#pragma once

#include "TimeKeeper.h"
#include "board.h" 

class CRule
{
	CTimeKeeper		TimeKeeper;

	int Handle;		//”wŒi

public:
	CRule();
	~CRule();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//“G‚ğ“|‚µ‚½ê‡	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//‰æ–Êã•”‚Ü‚Åƒpƒlƒ‹‚ª—ˆ‚½ê‡

	inline bool CheckGameEnd() { return TimeKeeper.GetFlag(); }
	//ŠÔØ‚ê
};
