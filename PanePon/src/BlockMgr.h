#pragma once

#include "DxLib.h"
#include <vector>
#include "Move.h"
#include "Block.h"
#include <time.h>
#include "define.h"



enum {		//パネルの種類	()
	eRed,
	eBlue,
	eGreen,
	eCyan,
	eYellow,
	ePurple,
	eBlank
};

class CBlockMgr
{
	int Handle[6];						//画像ハンドル
	int OjamaHandle[5];
	std::vector<CBlock> Block[6];		//6*20のパネル配列生成

	CMove  Move;
	int handleB;						//画像ハンドル

	int HandleClear;					//画像ハンドル
	int HandleGameOver;					//画像ハンドル
	int HandlePanic;					//画像ハンドル

	int Counter;						//コントローラーから現在の時間を得るs

	bool flag = false;		//Game終了 フラグ
	int cnt = 0;
	int DrawFlag = 0;		//(0:普通,1:パニック状態,2:gameover,3:Finish

	void CheckPanicFlag();
	void CheckGameOver();

public:
	CBlockMgr();
	~CBlockMgr();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();


	void CreateBlock();//x,y,種類,存在
	void DeleteBlock();


	void Gravity();		//完成後、Moveに移動する
	void SwapBlock(int x, int y);
	
	void BlockInitializer(int y1, int y2);		//ブロックの配置を選別 引数:上下の範囲
												//二つ目は基本19。
	void MakeOjama(int i, int j ,CAnotherKind AnotherKind);

	//ゲーム終了判定
	inline bool GetFlag() { return flag; }

	void UpLiftDraw(double Uy) {
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				Block[i][j].UpLiftDraw(Uy);
			}
		}
	}

	inline CBlockMgr *GetThisPtr() { return this; }//自分自身を渡す。
	/*
	inline std::vector<CBlock> *GetBlockPtr() {		//中に入っているパネルを出す。
		std::vector<CBlock> *p = &Block[0];
		std::vector<CBlock> **pp = &p;
		*pp = &Block[0];
		return p; }
		*/

	inline std::vector<CBlock> *GetBlockPtr() {return Block;}

	inline int GetBlockKind(int x, int y) { return Block[x][y].GetKind();}
	inline bool GetBlockFlag(int x, int y) { return Block[x][y].GetFlag();}
	inline void SetBlockFlagTrue (int x, int y) {Block[x][y].SetFlag(true); }
	inline void SetBlockFlagFalse(int x, int y) { Block[x][y].SetFlag(false); }
	inline void SetBlockKind(int x, int y, int kind) {Block[x][y].SetKind(kind);}
	
	//お邪魔用
	inline CAnotherKind GetAnotherKind(int x, int y) { return Block[x][y].GetAnotherKind(); };
	inline void SetAnotherKind(int x, int y, CAnotherKind Anotherkind) { Block[x][y].SetAnotherKind(Anotherkind); }
	
	inline void SetIsOjama(int i, int j, bool isojama) { Block[i][j].SetIsOjama(isojama); }
	inline int GetIsOjama(int i, int j) { return Block[i][j].GetIsOjama(); }

		////スコアアタック用////
	inline int GetBlockCounter(int x, int y) { return Block[x][y].GetCounter(); }
	inline void SetBlockCounter(int x, int y, int Counter) { Block[x][y].SetCounter(Counter); }
	
	inline void ReduceBlockCounter(int x, int y) {
		int cnt = 0;
		cnt = Block[x][y].GetCounter();
		cnt--;
		Block[x][y].SetCounter(cnt);
	}

	inline int GetBlockStop(){ return DrawFlag; }	//コントローラーにゲームの状態を伝える

	inline void SetGameFinishFlag() { DrawFlag = 3; flag = true; }		//ゲーム終了+Finish
	
	//inline std::array<CBlock , 10> *GetBlockPtr() { return &Block; }
};



//(1)...削除された関数を参照しようとしています
//(2)...クラス型が必要です=クラスと見なされていない