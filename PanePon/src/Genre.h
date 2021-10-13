#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "define.h"
#include <iostream>
#include <string>
#include <fstream>


enum SelectMode
{
	ModeStart,			//スタート画面
	ModeGraph,			//画面選択
	ModeMode,			//モード選択
	ModeDifficulty,		//難易度選択
	ModeTimer,			//タイマー選択
	ModeChara			//キャラクタ選択
};

//メニュー画面クラス
class CGenre : public CBaseScene {
public :
	SelectMode Mode;

	int	 Bc;

	CGenre(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override ;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

private :
	/*int  Handle;
	int  Handle2;
	int  Title;*/	//画像なし
	int  Font00 = CreateFontToHandle(NULL, 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	int  Font01 = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	int  pointer = 250;
	int  color1, color2, color3, color4, color5;
	int tmp = 0;

	void SelectInit();
};