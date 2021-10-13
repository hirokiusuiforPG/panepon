#include "Delete.h"

//deleteに必要なのはBlock->GetFlag()と
//Block->SetExist()。
//ただしBlock->Deleting(消えている途中)が必要になるかも知れない。

//機能
//Swap() -> search() -> delete() -> BlockMgr と 
//Gravity() -> search() -> delete() -> BlockMgrを 通して削除要請が来る。(毎Blockごとに来ない。)
//Effectを表示している間は存在はしているので、Deletingが必要。
//Effectが終了したら存在を消す。


CDelete::CDelete() {			//Cursorはいらない
	
}

CDelete::~CDelete()
{
}

void CDelete::Initialize()	//CCursor *Cursor と CCursor *p で * = * を表している
{
}

void CDelete::Update()								//パネル全部に行う
{
	CheckDeleteBlock();								//updateに直接書いても良さそう。
}

void CDelete::CheckDeleteBlock()
{
	/*	内容(直接)
	for(int i = 0; i < 6; i++){						//vectorで6個用意してる。
		for(int j = 0; j < 19; j++){				//resize()使って20個用意してる。
			if(Block[i][j].GetFlag() == true){
													//ここにEffectが入る。 今は瞬時にパネルが消える。
				Block[i][j].SetExist() == false;
			}
		}
	}*/
	/*
	//間接									
	for (auto it1 = BlockMgr->GetBlockPtr()->begin(); it1 != BlockMgr->GetBlockPtr()->end(); it1++)
	{
		int t = 0;
		if (it1->GetFlag() == true)					//現状エラーは起きないが不可解な動きを見せる。
		{
			//printfDx("表示されてる。%d",t);		//ここで動作確認
			t++;
		}
	}
	*/

}

	//8月19日  デバック出来るようにした。
