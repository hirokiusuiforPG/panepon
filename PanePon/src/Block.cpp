#include "Block.h"

//diff		差分 パネル１つ分に満たないブロック
//			diff = diff % 60

CBlock::CBlock() {
	UpLiftDrawY = 0;			//せり上がり描画用
	Counter = 120;				//消えるのに2秒かかるってこと

	IsOjama = false;
	AnotherKind = AKnull;
	CounterFlag = 0;
}

void CBlock::Initialize(int posx, int posy, int kind, bool exist, bool flag, int rekind) {
	x = posx;					//x座標
	y = posy;					//y座標
	Kind = kind;				//種類
	Exist = exist;				//未使用
	Flag = flag;				//search()で使用。:パネルが消える状態であればfalse 
	Rekind = rekind;			//未使用
}

void CBlock::Update() {		//未使用
	BadRepair();			//バグ処理 Counterが減ったまま。
	//IsValid();
}

void CBlock::Draw(int handle) {
	if (AnotherKind == AKnull)
	{
		//画像が回転できる描写
		if (Counter >= 10) {//120
		DrawRotaGraph3F(x * 60 + 150, y * 60 - 170 - UpLiftDrawY, 30, 30, (double)cos((Counter/30.000) * PI), 1.0f, 0.0,  handle, true, false);
		}
		
		//DrawRotaGraphF(x * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
	}
	else
	{
		switch(AnotherKind)
		{
		case AKthree:
			DrawRotaGraphF((x + 1) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break; 
		case AKfour:
			DrawRotaGraphF((x + 1.5) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		case AKfive:
			DrawRotaGraphF((x + 2) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break; 
		case AKsix:
			DrawRotaGraphF((x + 2.6) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		case AKunchain:
			DrawRotaGraphF((x + 2.6) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		default:break;
		}
	}
}


//未使用
void CBlock::BadRepair() {	
	//Counterがバグで勝手に進んだ時、消えずに止まっていたら、フレームを120に戻す。
	if (5 <= Counter && Counter <= 115)	//値が変化中
	{
		if (CounterFlag == Counter)		//値が変化なし。
		{
			Counter = 120;				//カウンターを120に戻す。
			CounterFlag = 0;
		}
		CounterFlag = Counter;		//現在のCounterを保持
	}
	else if (Counter == 120)
	{
		CounterFlag = 0;
	}
	
}

void CBlock::IsValid() {
	/*
	if (Life <= 0) {
		Cnt++;
		if (Cnt > Block_DELAY)//敵と壁のエフェクト時間は同じ
			flag = false;
	}
	*/
}