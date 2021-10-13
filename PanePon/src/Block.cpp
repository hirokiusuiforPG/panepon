#include "Block.h"

//diff		���� �p�l���P���ɖ����Ȃ��u���b�N
//			diff = diff % 60

CBlock::CBlock() {
	UpLiftDrawY = 0;			//����オ��`��p
	Counter = 120;				//������̂�2�b��������Ă���

	IsOjama = false;
	AnotherKind = AKnull;
	CounterFlag = 0;
}

void CBlock::Initialize(int posx, int posy, int kind, bool exist, bool flag, int rekind) {
	x = posx;					//x���W
	y = posy;					//y���W
	Kind = kind;				//���
	Exist = exist;				//���g�p
	Flag = flag;				//search()�Ŏg�p�B:�p�l�����������Ԃł����false 
	Rekind = rekind;			//���g�p
}

void CBlock::Update() {		//���g�p
	BadRepair();			//�o�O���� Counter���������܂܁B
	//IsValid();
}

void CBlock::Draw(int handle) {
	if (AnotherKind == AKnull)
	{
		//�摜����]�ł���`��
		if (Counter >= 10) {//120
		DrawRotaGraph3F(x * 60 + 150, y * 60 - 170 - UpLiftDrawY, 30, 30, (double)cos((Counter/30.000) * PI), 1.0f, 0.0,  handle, true, false);
		}
		
		//DrawRotaGraphF(x * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
	}
	else
	{
		switch(AnotherKind)
		{
		case AKthree:
			DrawRotaGraphF((x + 1) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break; 
		case AKfour:
			DrawRotaGraphF((x + 1.5) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		case AKfive:
			DrawRotaGraphF((x + 2) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break; 
		case AKsix:
			DrawRotaGraphF((x + 2.6) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		case AKunchain:
			DrawRotaGraphF((x + 2.6) * 60 + 150, y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, handle, true);
			break;
		default:break;
		}
	}
}


//���g�p
void CBlock::BadRepair() {	
	//Counter���o�O�ŏ���ɐi�񂾎��A�������Ɏ~�܂��Ă�����A�t���[����120�ɖ߂��B
	if (5 <= Counter && Counter <= 115)	//�l���ω���
	{
		if (CounterFlag == Counter)		//�l���ω��Ȃ��B
		{
			Counter = 120;				//�J�E���^�[��120�ɖ߂��B
			CounterFlag = 0;
		}
		CounterFlag = Counter;		//���݂�Counter��ێ�
	}
	else if (Counter == 120)
	{
		CounterFlag = 0;
	}
	
}

void CBlock::IsValid() {
	/*
	if (Life <= 0) {
		Cnt++;
		if (Cnt > Block_DELAY)//�G�ƕǂ̃G�t�F�N�g���Ԃ͓���
			flag = false;
	}
	*/
}