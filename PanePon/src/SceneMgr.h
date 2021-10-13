#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Genre.h"
#include "Start.h"
#include "Achievement.h"

class CSceneMgr : public ISceneChanger, Task {
	CBaseScene* mScene;    //シーン管理変数
	eScene mNextScene;    //次のシーン管理変数
	bool ExitFlag;

public:
	CSceneMgr();
	void Initialize() override;//初期化
	void Finalize() override;//終了処理
	void Update() override;//更新
	void Draw() override;//描画

	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;

	inline bool State(){ return ExitFlag; }
};