#include "SysMgr.h"
static const char* luncherPath = "C:\\Users\\twdsa\\Desktop\\ランチャー展示用３\\ランチャー.exe";

CSysMgr::CSysMgr(){
	fps_count = 0;
	count0t = 0;
	memset(f, 0, sizeof(f));
	ave = 0;
	term = 0;
	i = 0;
	gnt = 0;
	t = 0;

	memset(title, '\0', sizeof(title));
}

CSysMgr::~CSysMgr(){
	//SceneMgr.Finalize();
	DxLib_End();
	//system(luncherPath);
}

void CSysMgr::MainLoop(){
	SceneMgr.Initialize();//シーンが変わるときに初期化
	while ((!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) && !SceneMgr.State()){//stateからExit_Fragの判定
		SceneMgr.Update();
		SceneMgr.Draw();
		fps_wait();
		draw_fps();
		CKey::Inst()->Update();
	}
}

//待機時間を計算
void CSysMgr::fps_wait(){
	if (fps_count == 0){//60フレームの1回目なら
		if (t == 0)//完全に最初ならまたない
			term = 0;
		else//前回記録した時間を元に計算
			term = count0t + 1000 - GetNowCount();
	}
	else    //待つべき時間=現在あるべき時刻-現在の時刻
		term = (int)(count0t + fps_count*(1000.0 / FLAME)) - GetNowCount();

	if (term>0)//待つべき時間だけ待つ
		Sleep(term);

	gnt = GetNowCount();

	if (fps_count == 0)//60フレームに1度基準を作る
		count0t = gnt;
	f[fps_count] = gnt - t;//１周した時間を記録
	t = gnt;
	//平均計算
	if (fps_count == FLAME - 1){
		ave = 0;
		for (i = 0; i<FLAME; i++)
			ave += f[i];
		ave /= FLAME;
	}
	fps_count = (++fps_count) % FLAME;
}

//fpsを表示
void CSysMgr::draw_fps(){
	sprintf_s(title, "FPS = [%.1f]", 1000 / ave);
	SetMainWindowText(title);
	return;
}