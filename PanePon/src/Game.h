#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "Controller.h"
#include "define.h"

//�Q�[����ʃN���X
class CGame : public CBaseScene {
	CController	Controller;



public :
	CGame(ISceneChanger* changer);

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;       //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};