#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "Controller.h"
#include "define.h"

//ゲーム画面クラス
class CGame : public CBaseScene {
	CController	Controller;



public :
	CGame(ISceneChanger* changer);

	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override;       //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

};