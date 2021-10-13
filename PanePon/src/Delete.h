#pragma once

#include "Cursor.h"
#include "BlockMgr.h"

class CDelete
{
	void CheckDeleteBlock();

public:
	CDelete();	//コンストラクタ
	~CDelete();

	void Initialize();	//BlockMgrのポインタを持ってくる。
	void Update();			//削除する
};