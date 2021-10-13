#include "Game.h"

extern int g_nDifficult;
extern int g_nTimer;
extern int g_nMode;

CGame ::CGame(ISceneChanger* changer) : CBaseScene(changer) {
}

//������
void CGame::Initialize() {
	Controller.Initialize();
};   



//�X�V
void CGame::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0 ) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Genre);//�V�[�������j���[�ɕύX
	}
	Controller.Update();

	if (Controller.CheckGameEnd3() == 1)		//�Q�[���I�[�o�[�ɂȂ�����
		mSceneChanger->ChangeScene(eScene_Game);
	else if (Controller.CheckGameEnd3() == 2)
		mSceneChanger->ChangeScene(eScene_Genre);
};


//�`��
void CGame::Draw(){
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
	//DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 'Esc'->genre");
	Controller.Draw();
}
; //�����Ă��Ȃ��Ă�����

