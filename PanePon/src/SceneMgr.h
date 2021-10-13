#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Genre.h"
#include "Start.h"
#include "Achievement.h"

class CSceneMgr : public ISceneChanger, Task {
	CBaseScene* mScene;    //�V�[���Ǘ��ϐ�
	eScene mNextScene;    //���̃V�[���Ǘ��ϐ�
	bool ExitFlag;

public:
	CSceneMgr();
	void Initialize() override;//������
	void Finalize() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;

	inline bool State(){ return ExitFlag; }
};