#pragma once

#include "Task.h"
#include "ISceneChanger.h"
#include "DxLib.h"

//�V�[���̊��N���X�B
class CBaseScene : public Task {
protected:
	ISceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public :
	CBaseScene(ISceneChanger* changer);
	virtual ~CBaseScene(){}
	virtual void Initialize() override {}    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override ;            //�`�揈�����I�[�o�[���C�h�B

};