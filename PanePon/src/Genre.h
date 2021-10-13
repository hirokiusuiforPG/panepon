#pragma once

#include "BaseScene.h"
#include "DxLib.h"
#include "key.h"
#include "define.h"
#include <iostream>
#include <string>
#include <fstream>


enum SelectMode
{
	ModeStart,			//�X�^�[�g���
	ModeGraph,			//��ʑI��
	ModeMode,			//���[�h�I��
	ModeDifficulty,		//��Փx�I��
	ModeTimer,			//�^�C�}�[�I��
	ModeChara			//�L�����N�^�I��
};

//���j���[��ʃN���X
class CGenre : public CBaseScene {
public :
	SelectMode Mode;

	int	 Bc;

	CGenre(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private :
	/*int  Handle;
	int  Handle2;
	int  Title;*/	//�摜�Ȃ�
	int  Font00 = CreateFontToHandle(NULL, 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	int  Font01 = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	int  pointer = 250;
	int  color1, color2, color3, color4, color5;
	int tmp = 0;

	void SelectInit();
};