#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "define.h"

//�Q�[����ʃN���X
class CAchievement : public CBaseScene {
public:
	CAchievement(ISceneChanger* changer);

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;       //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
};
