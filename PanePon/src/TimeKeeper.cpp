#include "TimeKeeper.h"

CTimeKeeper::CTimeKeeper()
{
	//Timer���c�莞�Ԃ�����
	Counter = 0;
	
	flag = false;
	//�Q�[���I���֐������Bupdate�Q��
}

void CTimeKeeper::Initialize(double time) {

}

void CTimeKeeper::Finalize() {
}

void CTimeKeeper::Update() {
	Counter = (Counter + 1) % 60;

	if (0 == Counter) {
		
	}

	if ( !flag ) {
			flag = true;
		
	}
}

void CTimeKeeper::Draw() {

}

void CTimeKeeper::FrameCnt() {

}
void CTimeKeeper::FallBlock() {

}

void CTimeKeeper::UpliftBlock() {

}