#include "Game.h"

extern int g_nDifficult;
extern int g_nTimer;
extern int g_nMode;

CGame ::CGame(ISceneChanger* changer) : CBaseScene(changer) {
}

//初期化
void CGame::Initialize() {
	Controller.Initialize();
};   



//更新
void CGame::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0 ) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Genre);//シーンをメニューに変更
	}
	Controller.Update();

	if (Controller.CheckGameEnd3() == 1)		//ゲームオーバーになったら
		mSceneChanger->ChangeScene(eScene_Game);
	else if (Controller.CheckGameEnd3() == 2)
		mSceneChanger->ChangeScene(eScene_Genre);
};


//描画
void CGame::Draw(){
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
	//DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 'Esc'->genre");
	Controller.Draw();
}
; //あってもなくてもいい

