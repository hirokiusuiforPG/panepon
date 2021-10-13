#include "SceneMgr.h"

int g_nDifficult = 0;
int g_nTimer = 0;
int g_nMode = 0;

CSceneMgr::CSceneMgr() : mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (CBaseScene*) new CStart(this);//start��ʂ���
	ExitFlag = false;
}

//������
void CSceneMgr::Initialize(){
	mScene->Initialize();//������������override
}	//CGame�����������Ă�H

//�I������
void CSceneMgr::Finalize(){
	mScene->Finalize();
}

//�X�V
void CSceneMgr::Update(){
	if(mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch(mNextScene){       //�V�[���ɂ���ď����𕪊�
		case eScene_Genre:        //���̉�ʂ����j���[�Ȃ�
			mScene = (CBaseScene*) new CGenre(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
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
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void CSceneMgr::Draw(){
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void CSceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}
