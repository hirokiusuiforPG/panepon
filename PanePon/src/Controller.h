#pragma once

#include "Cursor.h"
#include "BlockMgr.h"
#include "DeleteDecide.h"
#include "Rule.h"
#include "board.h" 

class CController
{
	CCursor			Cursor;
	CBlockMgr		BlockMgr;
	CDeleteDecide	DeleteDecide;

	CRule			Rule;

	int Handle1;		//背景
	int Handle2;		//背景
	int Handle3;		//隠し
	int Handle4;		//隠し

	int soundflag;
	
	int Timer;		//せり上げに使う。 UpLift();
	int UpLiftCnt;	//パネルのせり上げに使う 25回で1パネル分

	int Paneltop[6];

	bool ComboFlag;		//Combo()でつかう
	int ComboNum;		//Combo()で使う
	bool DeletingFlag;	//削除中だったらtrue

	int ScorePoint;		//Score,ruleで使う

	struct HSP {					//加算分のスコアを表示
		int point;					//得点
		int DrawTime;				//表示時間
		bool Flag;					//
	};

	int CheckPanic;	//この状態でパネルが１個分せりあがるとGameOver

	int ScoreCounter;

	int StageTime;

	////GameOver画面////
	int Cr;
	int GameEnd;		//この値によって次のシーンが決定する。
	int  Font00 = CreateFontToHandle(NULL, 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	int  Font01 = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	int  pointer = 420;
	//////////////////
	bool PauseMode;
	bool X_ButtonMode;		//xボタンでせり上げ

	void SwapBlock();
	int Search();
	void Delete();
	void Combo();

	void UpLift1();
	void UpLift2();

	void AddScore();

	void GameOver();

	void Pause();

	void TimeProcess();

	void X_button();			//xボタンでせり上げ

	void OjamaGravity();
	void OjamaPanelTop();
	void OjamaChange();
	void OjamaMakePanel(int i, int j, CAnotherKind Anotherkind);	//お邪魔をパネルに変換

	void OjamaPush();//お邪魔生成
	
	void SetOjama(int i, int j, CAnotherKind AnotherKind, bool flag);//お邪魔フラグをセットする。

public:
	CController();
	~CController();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//敵を倒した場合	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//画面上部までパネルが来た場合

	inline bool CheckGameEnd1() { return Rule.CheckGameEnd(); }
	//時間切れ
	inline bool CheckGameEnd2() { return BlockMgr.GetFlag(); }
	//画面上部までパネルが来た場合

	inline int CheckGameEnd3() { return GameEnd; }
};