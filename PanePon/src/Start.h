#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "define.h"

//�Q�[����ʃN���X
class CStart : public CBaseScene {
public:
	CStart(ISceneChanger* changer);


	int  Title;
	int	 Bc;
	int Block[6];

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;       //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

	int  Font00 = CreateFontToHandle(NULL, 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	int  Font01 = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	int  pointer = 250;
	int  color1, color2, color3, color4, color5;
	int tmp = 0;

};