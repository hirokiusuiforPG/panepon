#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "define.h"

//�ݒ��ʃN���X
class CConfig : public CBaseScene {
public :
    CConfig(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};