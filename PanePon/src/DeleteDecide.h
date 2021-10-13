#pragma once

#include "BaseObject.h"
#include "Cursor.h"
#include "BlockMgr.h"

#include "Search.h"
#include "Delete.h"

class CDeleteDecide
{
	CSearch Search;
	CDelete Delete;			//�N���X�p��(���L)

	void CalcScore();
	void CntCombo();

	template<typename T, typename U>
	void CheckHit(T a, U b) {
		double dx = abs(a->GetX() - b->GetX());
		double dy = abs(a->GetY() - b->GetY());
		double dr = a->GetHitRange() * a->GetHitRange() + b->GetHitRange() * b->GetHitRange();
		if (dx * dx + dy * dy < dr) {//�������Ă�
			a->ApplyDamage(b->GetDamage());
			b->ApplyDamage(a->GetDamage());
		}
	}

	//�{���ƃ��[�U�[�̓����蔻��p�̊֐��͌�X

public:
	CDeleteDecide();
	~CDeleteDecide();

	void Initialize();
	void Update();

	int CheckSearchBlock(int kind1, int kind2);

};