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

	int Handle;		//�w�i

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
	//�G��|�����ꍇ	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//��ʏ㕔�܂Ńp�l���������ꍇ

	inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//���Ԑ؂�
};
