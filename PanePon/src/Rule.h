#pragma once

#include "TimeKeeper.h"
#include "board.h" 

class CRule
{
	CTimeKeeper		TimeKeeper;

	int Handle;		//�w�i

public:
	CRule();
	~CRule();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//�G��|�����ꍇ	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//��ʏ㕔�܂Ńp�l���������ꍇ

	inline bool CheckGameEnd() { return TimeKeeper.GetFlag(); }
	//���Ԑ؂�
};
