#include "Controller.h"

extern int g_nDifficult;
extern int g_nTimer;
extern int g_nMode;

const char SE1[] = "dat/sound/break.wav";

CController::CController()
{	
	Cursor.Initialize(2, 11);
	Handle1 = LoadGraph("dat/img/PanePon_�w�i4.jpg");	//�w�i
	Handle2 = LoadGraph("dat/img/PanePon_�w�i5.png");	//�w�i
	Handle3 = LoadGraph("dat/img/PanePon_�w�i6.jpg");	//�B��
	Handle4 = LoadGraph("dat/img/PanePon_�w�i7.png");	//�B��

	Timer = 1;			//����(0)�͔������Ȃ�
	UpLiftCnt = 1;		//�p�l��1���z�u����̂Ɏg���B
	ComboFlag = false;	//�R���{������������true
	ComboNum = 0;		//���݂̃R���{��
	DeletingFlag = false;	//�폜����������true
	soundflag = 0;

	ScorePoint = 0;
	ScoreCounter = 0;

	for (int i = 0; i < 6; i++)
	{
		Paneltop[i] = 0;
	}

	////GameOver////
	Cr = GetColor(0, 0, 255);        // �F�̒l���擾
	GameEnd = 0;
	////////////////
	PauseMode = false;
	X_ButtonMode = false;

	StageTime = 60 * 60 * g_nTimer;
}

CController::~CController()
{
}

void CController::Initialize() {
	BlockMgr.Initialize();
	DeleteDecide.Initialize();
	Rule.Initialize();
	//DeleteDecide.Initialize(Screen.GetThisPtr(), Rule.GetThisPtr());
}

void CController::Update() {
	if (BlockMgr.GetBlockStop() < 2  && !PauseMode )			//�Q�[���I�[�o�[����
	{
		if (!X_ButtonMode)
		{
			Cursor.Update();				//�J�[�\��������
			BlockMgr.Update();				//����Block[][].update������

			SwapBlock();					//�p�l������
		}

		BlockMgr.Gravity();				//�d��
		Search();						//�p�l������
		Delete();						//�폜

		if (!DeletingFlag)				//�폜���łȂ���
		{
			X_button();
			UpLift1();					//����グ
		}
		OjamaPush();		//a�������Əo��

		OjamaChange();		//���ז�->�p�l���ϊ�
		OjamaPanelTop();
		OjamaGravity();

		Combo();						//�A���A��������
		AddScore();						//�����ŉ����B
		BlockMgr.Gravity();				//�d��
		TimeProcess();
	}

	if(BlockMgr.GetFlag() == true) {
		GameOver();
	}
	else
	{
		Pause();
	}
	Rule.Update();

	DeleteDecide.Update();
}

void CController::Draw() {
	if (g_nMode == 3)
	{
		DrawGraph(0, 0, Handle1, true);
	}
	else if(g_nMode == 2)
	{
		DrawGraph(0, 0, Handle2, true);
	}


	Rule.Draw();
	BlockMgr.Draw();
	Cursor.Draw();//��Ԏ�O

/*	if (!BlockMgr.GetFlag() && PauseMode == false)
	{
		if (ComboNum > 0)
		{
			printfDx("%d", ComboNum);
		}
	}*/


	if (BlockMgr.GetFlag())
	{
		DrawBox(500, 400, 850, 540, Cr, TRUE);    // �l�p�`��`��
		DrawStringToHandle(560, 420, "������x", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(560, 470, "��߂�", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(500, pointer, "��", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	}
	else if (PauseMode)
	{
		DrawBox(500, 400, 850, 540, Cr, TRUE);    // �l�p�`��`��
		DrawStringToHandle(560, 420, "������", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(560, 470, "��߂�", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(500, pointer, "��", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	}

	//DrawGraph(0, 0, Handle, true);//�w�i
	
	if (g_nMode == 2)
	{
		if (StageTime <= 0)
		{
			DrawStringToHandle(200, 220, "�t�B�j�b�V���I�I�I", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		}
	}

	//DrawStringToHandle(280, 450, "%d", StageTime / 60, GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	switch (g_nMode)
	{
	case 1: DrawFormatString(500, 250, GetColor(255, 105, 0), "�G���h���X�I�I");
		break;
	case 2:	DrawFormatString(500, 250, GetColor(255, 0, 0), "�c�莞�� : %d", StageTime / 60);
		break;
	case 3: DrawFormatString(500, 250, GetColor(255, 105, 0), "������܃A�^�b�N�I");
			DrawFormatString(500, 300, GetColor(255, 0, 0), "�c�莞�� : %d", StageTime / 60);

			/*DrawFormatString(700, 200, GetColor(120, 55, 155), "���ז��o��");
			DrawFormatString(700, 250, GetColor(100, 0, 255), "a �� ��1 : 1�~3�̂��ז�");
			DrawFormatString(700, 300, GetColor(100, 0, 255), "s �� ��2 : 1�~3�̂��ז�");
			DrawFormatString(700, 350, GetColor(100, 0, 255), "d �� ��3 : 1�~3�̂��ז�");
			DrawFormatString(700, 400, GetColor(100, 0, 255), "f �� ��4 : 1�~3�̂��ז�");
			DrawFormatString(700, 450, GetColor(100, 0, 255), "g �� 1�~4�̂��ז�");
			DrawFormatString(700, 500, GetColor(100, 0, 255), "h �� 1�~5�̂��ז�");
			DrawFormatString(700, 550, GetColor(100, 0, 255), "j �� 1�~6�̂��ז�");
			DrawFormatString(700, 600, GetColor(100, 0, 255), "k �� 2�~6�̂��ז�");*/
		break;
	default:
			break;
	}
	DrawFormatString(500, 200, GetColor(255, 0, 0), "�X�R�A : %d", ScorePoint);
	DrawBox(50, 705, 600, 710,GetColor(255,0,0),true);

	if (g_nMode == 3)
	{
		DrawGraph(0, 710, Handle3, false);
	}
	else if(g_nMode == 2)
	{
		DrawGraph(0, 710, Handle4, true);
	}

}

void CController::Finalize() {

}
void CController::UpLift1() 
{
	if (X_ButtonMode == false)//������ĂȂ�
	{
		//���b2.4�s�N�Z�� ����グ��	UpLiftRoutine
		if (Timer % (60 / (g_nDifficult + 4)) == 0)			//����グ�������A4�{�� 60 -> 15
		{
			UpLiftCnt++;					//�����ÂA����グ��
			BlockMgr.UpLiftDraw(2.4);		//����グ���A�ǉ�����
			Cursor.UpLiftDraw(2.4);			//����グ���A�ǉ�����
		}
		if (UpLiftCnt % 25 == 0)			//25�񂹂�グ����A
		{
			BlockMgr.CreateBlock();			//�u���b�N����
			BlockMgr.BlockInitializer(18, 19);		//18�s�ڂ̂�
			UpLift2();
			UpLiftCnt = 1;	//���|���R��������Ȃ��B
		}
	}
	else//������Ă鎞
	{
		if (Timer % 3 == 0)			//����グ�������A4�{�� 60 -> 15
		{
			UpLiftCnt++;					//�����ÂA����グ��
			BlockMgr.UpLiftDraw(2.4);		//����グ���A�ǉ�����
			Cursor.UpLiftDraw(2.4);			//����グ���A�ǉ�����
		}
		if (UpLiftCnt % 25 == 0)			//25�񂹂�グ����A
		{
			BlockMgr.CreateBlock();			//�u���b�N����
			BlockMgr.BlockInitializer(18, 19);		//18�s�ڂ̂�
			UpLift2();
			X_ButtonMode = false;

			UpLiftCnt = 1;	//���|���R��������Ȃ��B
		}
	}
	Timer++;
}

void CController::UpLift2()
{
	//Copy&Paste
	for (int i = 0; i < 6; i++)
	{
		for (int j = 5; j < 20 ; j++)//��ʓ�+����グ����
		{
			//1�u���b�N���㉺��kind������:�����Ə������
			int temp ;
			bool tempF;
			CAnotherKind temp1;
			int Ojamatemp;				//SetIsOjama()
			//�F�̂�
			temp = BlockMgr.GetBlockKind(i, j);							//�����̐F��ێ�
			BlockMgr.SetBlockKind(i,j,BlockMgr.GetBlockKind(i,j-1));	//�����ɏ�̃p�l���̐F
			BlockMgr.SetBlockKind(i, j - 1, temp);						//��̃p�l����temp�̐F

			//Delete��flag
																		
			//AnotherKind
			temp1 = BlockMgr.GetAnotherKind(i, j);
			BlockMgr.SetAnotherKind(i, j, BlockMgr.GetAnotherKind(i,j-1));
			BlockMgr.SetAnotherKind(i, j - 1, temp1);

			//SetIsOjama
			Ojamatemp = BlockMgr.GetIsOjama(i, j);
			BlockMgr.SetIsOjama(i, j, BlockMgr.GetIsOjama(i, j - 1));
			BlockMgr.SetIsOjama(i, j - 1, Ojamatemp);
		}
	}
	Cursor.UpLiftCursor();			//����グ�ׁ̈A1�p�l������ɏグ��
	Cursor.UpLiftDraw(0);			//1�p�l�������̕���	�̏���
	BlockMgr.UpLiftDraw(0);			//1�p�l�������̕��� �̏���
}

void CController::SwapBlock()		//
{
	int x = Cursor.GetX();
	int y = Cursor.GetY();
	if (Cursor.SwapBlock() == true)//�J�[�\���̒l�������Ă���B
	{
		if (BlockMgr.GetBlockFlag(x, y) == true && BlockMgr.GetBlockFlag(x + 1, y) == true)//�������łȂ�
		{
			if (BlockMgr.GetIsOjama(x, y) == false && BlockMgr.GetIsOjama(x+ 1, y) == false)//���ז��łȂ�
			{
				BlockMgr.SwapBlock(x, y);//�����̃u���b�N���Q��	
			}
		}
	}
}

int CController::Search() 
{
	int Cnt = 0;
	int i, j;

	for (i = 0; i < 6; i++)
	{
		int k = 5;
		int Num = 1;
		for (j = 6; j < 15; j++) {

			if (BlockMgr.GetBlockKind(i, k) == BlockMgr.GetBlockKind(i, j))	//�A�����Ă�����
			{
				if (BlockMgr.GetBlockKind(i, j) != 6)		//�󔒂łȂ��A�A�������F
				{		
					if (BlockMgr.GetBlockCounter(i, j) == 120)//�܂��A�폜���łȂ��B
					{
						Num++;
					}
					else//�������ɏ����Ă�����̂�������A
					{
						Num = 0;		//������̂���߂�
					}
				}
			}
			else
			{
				if (Num >= 3)			//3�ȏ�̌q����
				{
					for (; k < j; k++)
					{
						BlockMgr.SetBlockFlagFalse(i, k);
					}
					Cnt++;
				}
				Num = 1;
				k = j;
			}
		}
		if (Num >= 3)			//3�ȏ�̌q����
		{
			for (; k < j; k++)
			{
				BlockMgr.SetBlockFlagFalse(i, k);
			}
			Cnt++;
		}
	}
	for (j = 5; j < 15; j++)
	{
		int k = 0;
		int Num = 1;
		for (i = 1; i < 6; i++)
		{
			if (BlockMgr.GetBlockKind(k, j) == BlockMgr.GetBlockKind(i, j))
			{			
				if (BlockMgr.GetBlockKind(i, j) != 6)		//�󔒂łȂ��A�A�������F
				{
					if(BlockMgr.GetBlockCounter(i,j) == 120)//�폜���łȂ���
					{
						Num++;
					}
					else//�������ɏ����Ă�����̂�������A
					{
						Num = 0;		//������̂���߂�
					}

				}
			}
			else
			{
				if (Num >= 3)			//3�ȏ�̌q����
				{
					for (; k < i; k++)
					{
						BlockMgr.SetBlockFlagFalse(k, j);
					}
					Cnt++;
				}
				Num = 1;
				k = i;
			}
		}
		if (Num >= 3)			//3�ȏ�̌q����
		{
			for (; k < i; k++)
			{
				BlockMgr.SetBlockFlagFalse(k, j);
			}
			Cnt++;
		}
	}
	return Cnt;
}

void CController::Delete()
{
	int i, j;

	for (i = 0; i <6; i++)
	{
		for (j = 5; j < 15; j++)
		{
			if (BlockMgr.GetBlockFlag(i, j) == false)	//�폜����ON
			{
				if (BlockMgr.GetBlockCounter(i, j) <= 0)	//���ԍ��ŏ����B
				{
					BlockMgr.SetBlockKind(i, j, 6);		//6 = ��
					BlockMgr.SetBlockFlagTrue(i, j);	//�폜�I�����
					BlockMgr.SetBlockCounter(i, j, 120);	//�J�E���^�[��120�ɂ���B
					ComboFlag = true;					//combo()�Ŏg�p
					ScoreCounter++;
					soundflag = 1;
				}
				else {	//�폜����͏o���p�l���̃J�E���^�[�����炷�B
					//�J�E���^�[���}�C�i�X����B
					BlockMgr.ReduceBlockCounter(i, j);
				}
				//Delete.all  = true //�폜���肪�Ȃ��Ȃ�܂ŁAcombo�����Z�b�g���Ȃ�
				DeletingFlag = true;
			}
		}
	}
}

void CController::Combo()
{
	if (soundflag == 1)
	{
		PlaySoundFile("dat/sound/break.wav", DX_PLAYTYPE_BACK);
	}
	if (ComboFlag == true)
	{
		ComboNum++;
	}
	else if (DeletingFlag == false)
	{
			ComboNum = 0;		//�R���{
	}
	ComboFlag = false;
	DeletingFlag = false;
	soundflag = 0;
}

void CController::AddScore() {
	if (ScoreCounter > 1)
	{
		//�X�R�A�J�E���g
		ScorePoint = ScorePoint + (ScoreCounter + 100) * ComboNum * ScoreCounter;
		ScoreCounter = 0;
	}

}

void CController::GameOver()
{
	if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
	{
		switch (pointer)
		{
		case 420: GameEnd = 1; break;
		case 470: GameEnd = 2; break;//�V�[�����I������
		}
	}

	if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//������ɁB
		if (pointer != 420) {
			pointer -= 50;
		}
		else {
			pointer = 470;
		}
	}
	if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//������ɁB
		if (pointer != 470) {
			pointer += 50;
		}
		else {
			pointer = 420;
		}
	}


}

void CController::Pause()
{
	if (!BlockMgr.GetFlag())		//�Q�[���I�[�o�[�łȂ���
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_Q) == 1)
		{
			if (!PauseMode)
			{
				PauseMode = true;
			}
			else
			{
				PauseMode = false;
			}
		}
	}
	if (PauseMode == true)
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
		{
			switch (pointer)
			{
			case 420: PauseMode = false; break;
			case 470: GameEnd = 2; break;//�V�[�����I������
			}
		}

		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1)
		{		//������ɁB
			if (pointer != 420) {
				pointer -= 50;
			}
			else {
				pointer = 470;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1)
		{	//������ɁB
			if (pointer != 470) {
				pointer += 50;
			}
			else
			{
				pointer = 420;
			}
		}
	}
}

void CController::TimeProcess()
{
	if (g_nMode == 2 || g_nMode == 3)				//�X�R�A�A�^�b�N���[�h��������
	{
		if (StageTime > 0)			//���Ԑ�������
			StageTime--;
		if (StageTime == 0)
		{
			BlockMgr.SetGameFinishFlag();//�p�l���ɃQ�[���I����`����
		}
	}
}

void CController::X_button()
{
	if (!BlockMgr.GetFlag())		//�Q�[���I�[�o�[�łȂ���
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_X) > 1)	//x��������Ă���
		{
			X_ButtonMode = true;
		}
	}
}

void CController::OjamaGravity()	//�󔒂͂����őS��������
{
	//���ז���������B
	//���ז���AnotherKind�̒l�ɂ���āA�Q�Ƃ���top�̒l��ς���B
	//top��-1��AnotherKind���ړ�����B
	//Get����������
	//top���X�V����
	//�������炨�ז��𒲂ׂ�B
	
	int Maxtop = 0;		//��̍ő�̍����𓾂�
	

	for (int j = 15; j >= 0; j--)	//�c
	{
		//�����猩�Ă���
		for (int i = 0; i < 6; i++)	//��
		{
			if (BlockMgr.GetAnotherKind(i, j) != AKnull)	//���ז�������
			{
				switch (BlockMgr.GetAnotherKind(i, j))			//AnotherKind����
				{
				case AKnull:	//�������Ȃ�
					break;
				case AKthree:
					Maxtop = 20;			//�p�l���̒��_��ێ�
					for (int p = i; p < i + 3; p++)		//���R���ׂ�
					{
						if (Maxtop > Paneltop[p])		//��������
						{
							Maxtop = Paneltop[p];		//Maxtop���X�V
						}//top�ő�l���擾
					}
					//AnotherKind��top-1�ɍX�V
					if (j != Maxtop - 1)		//�ʒu���ς�鎞
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKthree);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//���̈ʒu���X�V

						for (int p = i; p < i + 3; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//�X�V
							BlockMgr.SetIsOjama(p, j, false);			//���������B
						}
					}
					//paneltop���X�V
					for (int p = i; p < i + 3; p++)//���̗�̕�����
					{
						Paneltop[p] = Maxtop - 1;		//top�̍X�V
					}
					break;
				case AKfour:	
					Maxtop = 20;			//������
					for (int p = i; p < i + 4; p++)		//��4���ׂ�
					{
						if (Maxtop > Paneltop[p])		//��������
						{
							Maxtop = Paneltop[p];		//Maxtop���X�V
						}//top�ő�l���擾
					}
					//AnotherKind��top-1�ɍX�V
					if (j != Maxtop - 1)		//�l���������Ƃ��̂�
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKfour);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//���̈ʒu���X�V

						for (int p = i; p < i + 4; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//�X�V
							BlockMgr.SetIsOjama(p, j, false);			//���������B
						}
					}
													//paneltop���X�V
					for (int p = i; p < i + 4; p++)	//���̗�̕�����
					{
						Paneltop[p] = Maxtop - 1;		//top�̍X�V
					}
					break;
				case AKfive:	
					Maxtop = 20;			//������
					for (int p = i; p < i + 5; p++)		//��5���ׂ�
					{
						if (Maxtop > Paneltop[p])		//��������
						{
							Maxtop = Paneltop[p];		//Maxtop���X�V
						}//top�ő�l���擾
					}
					//AnotherKind��top-1�ɍX�V
					if (j != Maxtop - 1)		//�l���������Ƃ��̂�
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKfive);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//���̈ʒu���X�V

						for (int p = i; p < i + 5; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//�X�V
							BlockMgr.SetIsOjama(p, j, false);			//���������B
						}
					}
																//paneltop���X�V
					for (int p = i; p < i + 5; p++)//���̗�̕�����
					{
						Paneltop[p] = Maxtop - 1;		//top�̍X�V
					}
					break;
				case AKsix:		
					Maxtop = 20;			//������
					for (int p = i; p < i + 6; p++)		//���R���ׂ�
					{
						if (Maxtop > Paneltop[p])		//��������
						{
							Maxtop = Paneltop[p];		//Maxtop���X�V
						}//top�ő�l���擾
					}
					//AnotherKind��top-1�ɍX�V
					if (j != Maxtop - 1)		//�l���������Ƃ��̂�
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKsix);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//���̈ʒu���X�V

						for (int p = i; p < i + 6; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//�X�V
							BlockMgr.SetIsOjama(p, j, false);			//���������B
						}
					}
																//paneltop���X�V
					for (int p = i; p < i + 6; p++)//���̗�̕�����
					{
						Paneltop[p] = Maxtop - 1;		//top�̍X�V
					}
					break;
				case AKunchain:
					Maxtop = 20;			//������
					for (int p = i; p < i + 6; p++)		//���R���ׂ�
					{
						if (Maxtop > Paneltop[p])		//��������
						{
							Maxtop = Paneltop[p];		//Maxtop���X�V
						}//top�ő�l���擾
					}
					//AnotherKind��top-1�ɍX�V
					if (j != Maxtop - 1)		//�l���������Ƃ��̂�
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKunchain);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//���̈ʒu���X�V

						for (int p = i; p < i + 6; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//�X�V
							BlockMgr.SetIsOjama(p, j, false);			//���������B
						}
					}
																//paneltop���X�V
					for (int p = i; p < i + 6; p++)//���̗�̕�����
					{
						Paneltop[p] = Maxtop - 1;		//top�̍X�V
					}
					break;
				default:
					break;
				}
			}//���_��������B
		}
	}
	//�S�f�[�^��������(��O����)
}

void CController::OjamaPanelTop()
{
	int top = 20;
	for (int i = 0; i < 6; i++)				//�e���
	{
		for (int j = 14; j >= 5; j--)		//�����瑖��
		{
			if (BlockMgr.GetBlockKind(i, j) < 6)		//�p�l���̎�
			{
				top = j;			//���W�擾
			}
		}
		Paneltop[i] = top;			//���W�ő�l��񂲂Ƃɕێ�
	}
}

void CController::OjamaChange()//�p�l���ϊ�
{
	bool Flag1 = false;		
	bool Flag2 = false;
	bool Flag3 = false;//three
	bool Flag4 = false;//three

	for (int j = 14; j >= 5; j--)//������
	{

		for (int i = 0; i < 4; i++)//���ɒ��ׂ�
		{
			if (BlockMgr.GetAnotherKind(i, j) != AKnull)		//���ז����݂��鎞
			{
				switch (BlockMgr.GetAnotherKind(i, j))			//AnotherKind����
				{
				case AKnull:	break;
				case AKthree:

					for (int p = i; p < i + 3; p++)		//3�̃u���b�N��
					{//�㉺���E������B

						if (Flag3 == true && p >= 4) {//p����є����Ȃ��悤��
						}
						else if (Flag4 == true && p <= 0) {
						}
						else if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);			//Ojama������
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);
						}
						else if (i >= 1)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//��	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKthree, false);
							}
						}
						else if (i <= 5)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//�E	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKthree, false);
							}
						}

					}
					if (i == 0 && Flag1 == true) {
						Flag3 = true;
					}
					if (i == 4 && Flag1 == true) {
						Flag4 = true;
					}

					break;
				case AKfour:
					for (int p = i; p < i + 4; p++)		//4�̃u���b�N��
					{//�㉺���E������B

						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);			//Ojama������
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);
						}
						else if (i >= 1)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//��	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfour, false);
							}
						}
						else if (i <= 5)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//�E	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfour, false);
							}
						}
					}
					break;
				case AKfive:
					for (int p = i; p < i + 5; p++)		//3�̃u���b�N��
					{//�㉺���E������B
						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);
							Flag2 = false;
						}
						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);			//Ojama������
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);
						}
						else if (i >= 1)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//��	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfive, false);
							}
						}
						else if (i <= 5)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//�E	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfive, false);
							}
						}

					}
					break;
				case AKsix:
					for (int p = i; p < i + 6; p++)		//3�̃u���b�N��
					{//�㉺���E������B
						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);
							Flag2 = false;
						}
						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);			//Ojama������
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//��	�אڂ��ď�����
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);
						}
						else if (i >= 1)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//��	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKsix, false);
							}
						}
						else if (i <= 5)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//�E	�אڂ��ď�����
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKsix, false);
							}
						}
					}
					break;
				case AKunchain:
					for (int p = i; p < i + 6; p++)		//3�̃u���b�N��
					{//�㉺���E������B
						if (Flag1 == true)
						{
							//OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //��	�אڂ��ď�����
						{
							Flag1 = true;
						//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);			//Ojama������
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//��	�אڂ��ď�����
						{
							Flag1 = true;
							//OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);
						}
						else if (i >= 1)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//��	�אڂ��ď�����
							{
								Flag1 = true;
							//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKsix);
								SetOjama(i, j, AKsix, true);
							}
						}
						else if (i <= 5)		//�͈͊O����
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//�E	�אڂ��ď�����
							{
								Flag1 = true;
							//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//�p�l���ɕϊ�
								BlockMgr.SetAnotherKind(i, j, AKsix);
								SetOjama(i, j, AKsix, true);
							}
						}

					}
					break;
				default:
						break;
				}
			}
		}
		if (Flag1 == true)
		{
			if (Flag2 == true)
			{
				Flag1 = false;
				Flag2 = false;
				Flag3 = false;
				Flag4 = false;
			}
			else
			{
				Flag2 = true;
			}
		}
	}
}

void CController::OjamaMakePanel(int i, int j, CAnotherKind Anotherkind)
{
	switch (Anotherkind)
	{
	case AKnull:	break;
	case AKthree:
		for (int p = i; p < i + 3; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//�u���b�N�𐶐�
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//�u���b�N�𐶐�
		}
		break;
	case AKfive:	
		for (int p = i; p < i + 5; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//�u���b�N�𐶐�
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//�u���b�N�𐶐�
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//�u���b�N�𐶐�
		}
		break;
	}
	
	BlockMgr.BlockInitializer(j, j + 1);		//�����Ȃ��悤�ɔz�u
}

//���ז����蓮�Ő���
void CController::OjamaPush()		
{
	int tmp = 0;
	switch (g_nDifficult)
	{
	case 1:tmp = GetRand(3000); break;
	case 2:tmp = GetRand(2000); break;
	case 3:tmp = GetRand(1500); break;
	case 4:tmp = GetRand(1000); break;
	}
	if (g_nMode == 3)
	{
		switch (tmp)
		{
		case 1:BlockMgr.MakeOjama(0, 0, AKthree); break;
		case 2:BlockMgr.MakeOjama(2, 0, AKthree); break;
		case 3:BlockMgr.MakeOjama(3, 0, AKthree); break;
		case 4:BlockMgr.MakeOjama(0, 0, AKfour); break;
		case 5:BlockMgr.MakeOjama(0, 0, AKfive); break;
	//	case 5:BlockMgr.MakeOjama(0, 0, AKunchain);
	//		BlockMgr.MakeOjama(0, 1, AKsix);
			break;
		default:break;
		}
		/*
		//�f�o�b�N�p
		if (CKey::Inst()->GetKey(KEY_INPUT_A) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_S) == 1)
		{
			BlockMgr.MakeOjama(1, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_D) == 1)
		{
			BlockMgr.MakeOjama(2, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_F) == 1)
		{
			BlockMgr.MakeOjama(3, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_G) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKfour);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_H) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKfive);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_J) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKsix);
		}
		
		if (CKey::Inst()->GetKey(KEY_INPUT_K) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKunchain);
			BlockMgr.MakeOjama(0, 1, AKsix);
		}
		*/
	}
}

//���ז��t���O���Z�b�g����B
void CController::SetOjama(int i, int j, CAnotherKind AnotherKind, bool flag)
{
	switch (AnotherKind)		//AnotherKind�̒l�ɂ���āA
	{
	case AKnull:break;
	case AKthree:
		for (int p = i; p < i + 3; p++)		//3�̃u���b�N�̃t���O��false�ɂ���B
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//�t���O��false�ɂ���
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//�t���O��true�ɂ���
			}
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)		//3�̃u���b�N�̃t���O��false�ɂ���B
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//�t���O��false�ɂ���
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//�t���O��true�ɂ���
			}
		}
		break;
	case AKfive:
		for (int p = i; p < i + 5; p++)		//3�̃u���b�N�̃t���O��false�ɂ���B
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//�t���O��false�ɂ���
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//�t���O��true�ɂ���
			}
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)		//3�̃u���b�N�̃t���O��false�ɂ���B
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//�t���O��false�ɂ���
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//�t���O��true�ɂ���
			}
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)		//3�̃u���b�N�̃t���O��false�ɂ���B
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//�t���O��false�ɂ���
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//�t���O��true�ɂ���
			}
		}
		break;

	default:
		break;
	}
}
