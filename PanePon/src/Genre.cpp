#include "Genre.h"

extern int g_nDifficult;
extern int g_nTimer;
extern int g_nMode;

CGenre::CGenre(ISceneChanger* changer) : CBaseScene(changer){
	Mode = ModeGraph;
	color1 = 0, color2 = 255, color3 = 255, color4 = 255, color5 = 255;
	Bc = LoadGraph("dat/img/PanePon_背景3.png");
}

//初期化
void CGenre::Initialize(){
}

//更新
void CGenre::Update(){
	switch (Mode)
	{
	case ModeStart:
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
			Mode = ModeGraph;
		}
		break;
	case ModeGraph:										//画面選択
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
			switch (pointer)
			{
			case 250: Mode = ModeMode; break;
			case 300: break;
			case 350: mSceneChanger->ChangeScene(eScene_Achievement); break;
			case 400: mSceneChanger->ChangeScene(eScene_Config); break;
			case 450: mSceneChanger->ChangeScene(eScene_Start); break;	//シーンを終了する
			}
		}
		if (CheckHitKey(KEY_INPUT_G) != 0) {//Gキーが押されていたら
			//mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			//Mode = ModeMode;
		}
		if (CheckHitKey(KEY_INPUT_C) != 0) {//Cキーが押されていたら
			//mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
		}
		if (CheckHitKey(KEY_INPUT_A) != 0) {//Aキーが押されていたら
			//mSceneChanger->ChangeScene(eScene_Achievement);//シーンを設定画面に変更
		}
		/*if (CheckHitKey(KEY_INPUT_S) != 0) {//Sキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Start);//シーンを設定画面に変更
		}
		*/
		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//矢印を上に。
			tmp = color1;
			color1 = color2;
			color2 = color3;
			color3 = color4;
			color4 = color5;
			color5 = tmp;
			if (pointer != 250) {
				pointer -= 50;
			}
			else {
				pointer = 450;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//矢印を上に。
			tmp = color5;
			color5 = color4;
			color4 = color3;
			color3 = color2;
			color2 = color1;
			color1 = tmp;
			if (pointer != 450) {
				pointer += 50;
			}
			else {
				pointer = 250;
			}
		}
		break;
	case ModeMode:								//ジャンル選択
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
			switch (pointer)
			{
			case 250: g_nMode = 2; Mode = ModeDifficulty; SelectInit(); break;
			case 300: g_nMode = 3; Mode = ModeDifficulty; SelectInit(); break;
			case 350: g_nMode = 1; Mode = ModeDifficulty; SelectInit(); break;
			case 400: SelectInit(); break;
			case 450: g_nMode = 0; Mode = ModeGraph; SelectInit(); break;//シーンを移動する
			default:
				break;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//矢印を上に。
			tmp = color1;
			color1 = color2;
			color2 = color3;
			color3 = color4;
			color4 = color5;
			color5 = tmp;
			if (pointer != 250) {
				pointer -= 50;
			}
			else {
				pointer = 450;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//矢印を上に。
			tmp = color5;
			color5 = color4;
			color4 = color3;
			color3 = color2;
			color2 = color1;
			color1 = tmp;
			if (pointer != 450) {
				pointer += 50;
			}
			else {
				pointer = 250;
			}
		}
		break;


	case ModeDifficulty:									//難易度選択	
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
			if (g_nMode == 2 || g_nMode == 3)			//タイムアタックかお邪魔アタック
			{
				switch (pointer)
				{
				case 250: g_nDifficult = 1; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 300: g_nDifficult = 2; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 350: g_nDifficult = 3; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 400: g_nDifficult = 4; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 450: g_nDifficult = 0; g_nTimer = 0; Mode = ModeMode; SelectInit(); break;//シーンを移動する
				default:
					break;
				}
			}
			else
			{
				switch (pointer)
				{
				case 250: g_nDifficult = 1; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 300: g_nDifficult = 2; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 350: g_nDifficult = 3; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 400: g_nDifficult = 4; g_nTimer = 1; Mode = ModeChara; SelectInit(); break;
				case 450: g_nDifficult = 0; g_nTimer = 0; Mode = ModeMode; SelectInit(); break;//シーンを移動する
				default:
					break;
				}
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//矢印を上に。
			tmp = color1;
			color1 = color2;
			color2 = color3;
			color3 = color4;
			color4 = color5;
			color5 = tmp;
			if (pointer != 250) {
				pointer -= 50;
			}
			else {
				pointer = 450;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//矢印を上に。
			tmp = color5;
			color5 = color4;
			color4 = color3;
			color3 = color2;
			color2 = color1;
			color1 = tmp;
			if (pointer != 450) {
				pointer += 50;
			}
			else {
				pointer = 250;
			}
		}
		break;
		
	case ModeTimer:											//制限時間設定
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
			switch (pointer)
			{
			case 250: g_nTimer = 1;		Mode = ModeChara; SelectInit(); break;
			case 300: g_nTimer = 2;		Mode = ModeChara; SelectInit(); break;
			case 350: g_nTimer = 5;		Mode = ModeChara; SelectInit(); break;
			case 400: g_nTimer = 0;		Mode = ModeDifficulty; SelectInit(); break;//シーンを移動する
			default:
				break;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//矢印を上に。
			tmp = color1;
			color1 = color2;
			color2 = color3;
			color3 = color4;
			color4 = tmp;
			if (pointer != 250) {
				pointer -= 50;
			}
			else {
				pointer = 400;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//矢印を下に。
			tmp = color4;
			color4 = color3;
			color3 = color2;
			color2 = color1;
			color1 = tmp;
			if (pointer != 400) {
				pointer += 50;
			}
			else {
				pointer = 250;
			}
		}
		break;

	case ModeChara:	mSceneChanger->ChangeScene(eScene_Game); break;		//キャラ選択

	default:
		break;
	}

	//キャンセルキー
	if (CKey::Inst()->GetKey(KEY_INPUT_X) == 1)
	{
		switch (Mode)
		{
		case ModeStart:		SelectInit(); break;								//スタート画面
		case ModeGraph:		SelectInit(); break;								//画面選択
		case ModeMode:		Mode = ModeGraph;		SelectInit(); break;		//セレクト画面
		case ModeDifficulty:Mode = ModeMode;		SelectInit(); break;		//難易度選択画面
		case ModeTimer:		Mode = ModeDifficulty;	SelectInit(); break;		//時間設定画面
		case ModeChara:		Mode = ModeTimer;		SelectInit(); break;		//キャラ選択画面
			break;
		default:
			break;
		}
	}
};

//描画
void CGenre::Draw(){
	DrawGraph(0, 0, Bc, true);
	//DrawStringToHandle(0, 0, "genre", GetColor(255, 255, 255), Font00);

	switch (Mode)
	{
	case ModeStart:
		DrawStringToHandle(250, 250, "スタート", GetColor(0, 0, 0), Font01, GetColor(220, color1, color1));
		break;
	case ModeGraph:
		DrawStringToHandle(250, 250, "一人で遊ぶ", GetColor(0,0,0), Font01, GetColor(220, color1, color1));
		DrawStringToHandle(250, 300, "二人で遊ぶ (未実装)", GetColor(0, 0, 0), Font01, GetColor(220, color2, color2));
		DrawStringToHandle(250, 350, "実績 (未実装)", GetColor(0, 0, 0), Font01, GetColor(220, color3, color3));
		DrawStringToHandle(250, 400, "コンフィグ (未実装)", GetColor(0, 0, 0), Font01, GetColor(220, color4, color4));
		DrawStringToHandle(250, 450, "タイトル画面へ", GetColor(0, 0, 0), Font01, GetColor(220, color5, color5));
		break;
	case ModeMode:
		DrawStringToHandle(250, 250, "スコアアタック", GetColor(0, 0, 0), Font01, GetColor(220, color1, color1));
		DrawStringToHandle(250, 300, "おじゃまアタック", GetColor(0, 0, 0), Font01, GetColor(220, color2, color2));
		DrawStringToHandle(250, 350, "エンドレス", GetColor(0, 0, 0), Font01, GetColor(220, color3, color3));
		DrawStringToHandle(250, 400, "ＣＰＵ対戦 (未実装)", GetColor(0, 0, 0), Font01, GetColor(220, color4, color4));
		DrawStringToHandle(250, 450, "戻る", GetColor(0, 0, 0), Font01, GetColor(220, color5, color5));
		break;
	case ModeDifficulty:
		DrawStringToHandle(250, 250, "難易度-やさしい", GetColor(0, 0, 0), Font01, GetColor(220, color1, color1));
		DrawStringToHandle(250, 300, "難易度-普通", GetColor(0, 0, 0), Font01, GetColor(220, color2, color2));
		DrawStringToHandle(250, 350, "難易度-難しい", GetColor(0, 0, 0), Font01, GetColor(220, color3, color3));
		DrawStringToHandle(250, 400, "難易度-難ムズ", GetColor(0, 0, 0), Font01, GetColor(220, color4, color4));
		DrawStringToHandle(250, 450, "戻る", GetColor(0, 0, 0), Font01, GetColor(220, color5, color5));
		break;
	case ModeTimer:
		DrawStringToHandle(250, 250, "タイマー - 1分", GetColor(0, 0, 0), Font01, GetColor(220, color1, color1));
		DrawStringToHandle(250, 300, "タイマー - 2分　", GetColor(0, 0, 0), Font01, GetColor(220, color2, color2));
		DrawStringToHandle(250, 350, "タイマー - 5分", GetColor(0, 0, 0), Font01, GetColor(220, color3, color3));
		DrawStringToHandle(250, 400, "戻る", GetColor(0, 0, 0), Font01, GetColor(220, color4, color4));
		break;
	case ModeChara:break;
	default:
		break;
	}
		DrawStringToHandle(180, pointer, "→",			 GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	//DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 'a'->achievement");
}

void CGenre::SelectInit()
{
	pointer = 250;
	color1 = 0, color2 = 255, color3 = 255, color4 = 255, color5 = 255;
}
