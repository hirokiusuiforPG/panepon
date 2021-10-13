#include "DeleteDecide.h"


CDeleteDecide::CDeleteDecide(){
}


CDeleteDecide::~CDeleteDecide(){
}

void CDeleteDecide::Initialize() {
	Search.Initialize();
	Delete.Initialize();
}

void CDeleteDecide::Update() {
	Search.Update();
	Delete.Update();
	/*
	CalcScore(); {
	}
	CntCombo(); {
	}
	*/
}

void CDeleteDecide::CalcScore() {

}

void CDeleteDecide::CntCombo() {

}


int CDeleteDecide::CheckSearchBlock(int kind1, int kind2)
{
	int tmp;

	tmp = Search.CheckSearchBlock(kind1, kind2);

	return tmp;
}

