#include "DxLib.h"
#include "SysMgr.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	SetOutApplicationLogValidFlag(false);		//���O�o�͂��Ȃ�
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOWSIZE_X, WINDOWSIZE_Y, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowSizeChangeEnableFlag(true);		//�E�B���h�E�T�C�Y�����R�ɕύX�ł���
	SetAlwaysRunFlag(TRUE);						//�E�B���h�E���m���A�N�e�B�u�ł����s

	CSysMgr SysMgr;

	SysMgr.MainLoop();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}