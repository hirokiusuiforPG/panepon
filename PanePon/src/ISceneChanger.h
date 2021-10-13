#pragma once

typedef enum {
	eScene_Genre,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Config,  //�ݒ���
	eScene_Exit,
	eScene_None,    //����
	eScene_Start,
	eScene_Achievement,
} eScene ;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};