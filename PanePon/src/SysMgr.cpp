#include "SysMgr.h"
static const char* luncherPath = "C:\\Users\\twdsa\\Desktop\\�����`���[�W���p�R\\�����`���[.exe";

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
	SceneMgr.Initialize();//�V�[�����ς��Ƃ��ɏ�����
	while ((!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) && !SceneMgr.State()){//state����Exit_Frag�̔���
		SceneMgr.Update();
		SceneMgr.Draw();
		fps_wait();
		draw_fps();
		CKey::Inst()->Update();
	}
}

//�ҋ@���Ԃ��v�Z
void CSysMgr::fps_wait(){
	if (fps_count == 0){//60�t���[����1��ڂȂ�
		if (t == 0)//���S�ɍŏ��Ȃ�܂��Ȃ�
			term = 0;
		else//�O��L�^�������Ԃ����Ɍv�Z
			term = count0t + 1000 - GetNowCount();
	}
	else    //�҂ׂ�����=���݂���ׂ�����-���݂̎���
		term = (int)(count0t + fps_count*(1000.0 / FLAME)) - GetNowCount();

	if (term>0)//�҂ׂ����Ԃ����҂�
		Sleep(term);

	gnt = GetNowCount();

	if (fps_count == 0)//60�t���[����1�x������
		count0t = gnt;
	f[fps_count] = gnt - t;//�P���������Ԃ��L�^
	t = gnt;
	//���όv�Z
	if (fps_count == FLAME - 1){
		ave = 0;
		for (i = 0; i<FLAME; i++)
			ave += f[i];
		ave /= FLAME;
	}
	fps_count = (++fps_count) % FLAME;
}

//fps��\��
void CSysMgr::draw_fps(){
	sprintf_s(title, "FPS = [%.1f]", 1000 / ave);
	SetMainWindowText(title);
	return;
}