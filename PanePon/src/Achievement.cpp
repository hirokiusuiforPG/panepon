#include "Achievement.h"

CAchievement::CAchievement(ISceneChanger* changer) : CBaseScene(changer) {

}


//初期化
void CAchievement::Initialize()
{
};


//更新
void CAchievement::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Genre);//シーンをメニューに変更
	}
};


//描画
void CAchievement::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Achievement");
	DrawFormatString(0, WINDOWSIZE_Y-20, GetColor(255, 255, 255), "push 'Esc'->genre");
}
