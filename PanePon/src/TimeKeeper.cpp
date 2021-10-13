#include "TimeKeeper.h"

CTimeKeeper::CTimeKeeper()
{
	//Timerが残り時間を持つ
	Counter = 0;
	
	flag = false;
	//ゲーム終了関数を作る。update参照
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