#pragma once

#include "Cursor.h"
#include "BlockMgr.h"

class CDelete
{
	void CheckDeleteBlock();

public:
	CDelete();	//�R���X�g���N�^
	~CDelete();

	void Initialize();	//BlockMgr�̃|�C���^�������Ă���B
	void Update();			//�폜����
};