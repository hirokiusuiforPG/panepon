#include "SceneMgr.h"

int g_nDifficult = 0;
int g_nTimer = 0;
int g_nMode = 0;

CSceneMgr::CSceneMgr() : mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (CBaseScene*) new CStart(this);//start画面から
	ExitFlag = false;
}

//初期化
void CSceneMgr::Initialize(){
	mScene->Initialize();//初期化処理をoverride
}	//CGameを初期化してる？

//終了処理
void CSceneMgr::Finalize(){
	mScene->Finalize();
}

//更新
void CSceneMgr::Update(){
	if(mNextScene != eScene_None){    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;
		switch(mNextScene){       //シーンによって処理を分岐
		case eScene_Genre:        //次の画面がメニューなら
			mScene = (CBaseScene*) new CGenre(this);   //メニュー画面のインスタンスを生成する
			break;//以下略
		case eScene_Game:
			mScene = (CBaseScene*) new CGame(this);
			break;
		case eScene_Config:
			mScene = (CBaseScene*) new CConfig(this);
			break;
		case eScene_Exit:
			mScene = (CBaseScene*) new CGenre(this);
			ExitFlag = true;
			break;
		case eScene_Start:
			mScene = (CBaseScene*) new CStart(this);
			break;
		case eScene_Achievement:
			mScene = (CBaseScene*) new CAchievement(this);
			break;
		}
		mNextScene = eScene_None;    //次のシーン情報をクリア
		mScene->Initialize();    //シーンを初期化
	}

	mScene->Update(); //シーンの更新
}

//描画
void CSceneMgr::Draw(){
	mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void CSceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;    //次のシーンをセットする
}
