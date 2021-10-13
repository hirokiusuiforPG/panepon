#pragma once

#include "DxLib.h"

class CSearch
{
	
public:
	CSearch();	//コンストラクタ
	~CSearch();

	int CheckSearchBlock(int kind1, int kind2);

	void Initialize();	
	void Update();			//削除する
};


