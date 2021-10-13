#include "Achievement.h"

CAchievement::CAchievement(ISceneChanger* changer) : CBaseScene(changer) {

}


//������
void CAchievement::Initialize()
{
};


//�X�V
void CAchievement::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Genre);//�V�[�������j���[�ɕύX
	}
};


//�`��
void CAchievement::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Achievement");
	DrawFormatString(0, WINDOWSIZE_Y-20, GetColor(255, 255, 255), "push 'Esc'->genre");
}
