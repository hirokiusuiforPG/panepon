#include "Config.h"

CConfig::CConfig(ISceneChanger* changer) : CBaseScene(changer){

}

//������
void CConfig::Initialize(){
	
}

//�X�V
void CConfig::Update(){
	if(CheckHitKey(KEY_INPUT_ESCAPE) != 0) {			//Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Genre);	//�V�[�������j���[�ɕύX
	}
}

//�`��
void CConfig::Draw(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "config");
	DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 'Esc'->genre");
}
