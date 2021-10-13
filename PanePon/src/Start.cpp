#include "Start.h"

CStart ::CStart(ISceneChanger* changer) : CBaseScene(changer) {
	Title = LoadGraph("dat/img/panepon_title.png");
	Bc = LoadGraph("dat/img/PanePon_�w�i3.png");

	Block[0] = LoadGraph("dat/img/Block0.jpg");
	Block[1] = LoadGraph("dat/img/Block1.jpg");
	Block[2] = LoadGraph("dat/img/Block2.jpg");
	Block[3] = LoadGraph("dat/img/Block3.jpg");
	Block[4] = LoadGraph("dat/img/Block4.jpg");
	Block[5] = LoadGraph("dat/img/Block5.jpg");
}

//������
void CStart::Initialize()
{
};



//�X�V
void CStart::Update() {
	if (CheckHitKey(KEY_INPUT_S) != 0) { //Enter�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Genre);//�V�[�������j���[�ɕύX
	}
	if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1) {
		mSceneChanger->ChangeScene(eScene_Genre);
	}
};


//�`��
void CStart::Draw() {
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "start");
	//DrawFormatString(0, WINDOWSIZE_Y - 20, GetColor(255, 255, 255), "push 's'->start");
	DrawGraph(0, 0, Bc, true);
	//DrawGraph(100, 300, Bc, true);
	DrawGraph(120, 150, Title, true);
	DrawStringToHandle(100, 300, "Enter �� Z �� <<�X�^�[�g>>", GetColor(255,255,255), Font01, GetColor(220,0,0));

	DrawGraph(700, 500, Block[0], true);
	DrawGraph(770, 500, Block[1], true);
	DrawGraph(840, 500, Block[2], true);
	DrawGraph(700, 570, Block[3], true);
	DrawGraph(770, 570, Block[4], true);
	DrawGraph(840, 570, Block[5], true);
}
; //�����Ă��Ȃ��Ă�����

