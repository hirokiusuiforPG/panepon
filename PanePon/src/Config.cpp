#include "Config.h"

CConfig::CConfig(ISceneChanger* changer) : CBaseScene(changer){

}

//初期化
void CConfig::Initialize(){
	
}

//更新
void CConfig::Update(){
	if(CheckHitKey(KEY_INPUT_ESCAPE) != 0) {			//Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Genre);	//シーンをメニューに変更
	}
}

//描画
void CConfig::Draw(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "config");
	DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 'Esc'->genre");
}
