#include "DxLib.h"
#include "SysMgr.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	SetOutApplicationLogValidFlag(false);		//ログ出力しない
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSizeChangeEnableFlag(true);		//ウィンドウサイズを自由に変更できる
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行

	CSysMgr SysMgr;

	SysMgr.MainLoop();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}