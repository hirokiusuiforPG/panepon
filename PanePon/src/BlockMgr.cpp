#include "BlockMgr.h"

extern int g_nDifficult;
extern int g_nMode;

CBlockMgr::CBlockMgr()
{
	Handle[0] = LoadGraph("dat/img/Block0.jpg");
	Handle[1] = LoadGraph("dat/img/Block1.jpg");
	Handle[2] = LoadGraph("dat/img/Block2.jpg");
	Handle[3] = LoadGraph("dat/img/Block3.jpg");
	Handle[4] = LoadGraph("dat/img/Block4.jpg");
	Handle[5] = LoadGraph("dat/img/Block5.jpg");
	OjamaHandle[0] = LoadGraph("dat/img/Ojama1.jpg");//3
	OjamaHandle[1] = LoadGraph("dat/img/Ojama2.jpg");//4
	OjamaHandle[2] = LoadGraph("dat/img/Ojama3.jpg");//5
	OjamaHandle[3] = LoadGraph("dat/img/Ojama4.jpg");//6
	OjamaHandle[4] = LoadGraph("dat/img/Ojama5.jpg");//x
	handleB = LoadGraph("dat/img/PanelBoard3.png");

	flag = false;
	HandleClear = LoadGraph("dat/img/clear.png");
	HandleGameOver = LoadGraph("dat/img/GameOver.png");
	HandlePanic = LoadGraph("dat/img/Panic.png");

	//Block��6*20��
	for (int i = 0; i < 6; i++)
	{
		Block[i].resize(20);//2�����ɂ���
	}

	//***************************************
	//�t�@�C���ǂݍ���
	int n, num, i, fp;
	char fname[32] = { "dat/csv/PanelInit.csv" };	
	int input[64];
	char inputc[64];

	//�f�[�^�ۑ��p�̕ϐ�
	double cx, cy;
	int ckind, crekind;
	bool cexist, cflag;

	//�Ƃ肠����5��
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//���̒��g��Init�ł�낤�B
			Block[i][j].SetX(i);
			Block[i][j].SetY(j);
			Block[i][j].SetFlag(true);		//���ߓI�ɂ́A�폜��:false ����:true
			Block[i][j].SetKind(6);			//��
			//CreateBlock(i, j, 1, 1, 1, 1);
		}
	}
	
	//�p�l���z�u
	for (int i = 0; i < 6; i++)
	{
		for (int j = 13; j < 18; j++)	//������Q��Ƀu���b�N��\��
		{
			Block[i][j].SetKind(GetRand(100000) % (g_nDifficult + 2));//�F�����߂�
		}
	}
//	Block[3][12].SetFlag(true);//���R�A���R�̃u���b�N�𑶍݂�����B
	Block[3][12].SetKind(2);
//	Block[1][13].SetFlag(true);//���Q�A���Q�̃u���b�N�̑��݂������B
	Block[1][13].SetKind(6);	//�󔒁A(flag == false:kind = 6)
	
	BlockInitializer(5,19);		//�����z�u


	/*
	fp = FileRead_open(fname);//�t�@�C���ǂݍ���
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//�ŏ���2�s�ǂݔ�΂�
		while (FileRead_getc(fp) != '\n');

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1�����擾����
			if (inputc[i] == '/') {//�X���b�V���������
				while (FileRead_getc(fp) != '\n');//���s�܂Ń��[�v
				i = -1;//�J�E���^���ŏ��ɖ߂���
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//�J���}�����s�Ȃ�
				inputc[i] = '\0';//�����܂ł𕶎���Ƃ�
				break;
			}
			if (input[i] == EOF) {//�t�@�C���̏I���Ȃ�
				goto EXFILE;//�I��
			}
		}
		switch (num) {
		case 0: cx = atof(inputc); break;
		case 1: cy = atof(inputc); break;
		case 2: ckind = atoi(inputc); break;
		case 3: cexist = atoi(inputc); break;
		case 4: cflag = atoi(inputc); break;
		case 5: crekind = atoi(inputc); break;
		}
		num++;
		if (num == 6) {
			num = 0;
			n++;
			CreateBlock(cx, cy, ckind, cexist, cflag, crekind);	
			//�t�@�C������Q��
		}
	}
EXFILE:
	FileRead_close(fp);
	//***********************************************

	Counter = 0;
	//�Q�[���I���֐������Bupdate�Q��
	*/
}

CBlockMgr::~CBlockMgr()
{
}

void CBlockMgr::Initialize() {
}

void CBlockMgr::Finalize() {
}

void CBlockMgr::Update() {
	//Move.Update();
	//Gravity();			//����������AMove�Ɉړ�

	//Block.Update			//�����ƃo�O��B
	for (int i = 0; i < 6; i++)
	{
		for (int j = 6; j < 15; j++)
		{
			Block[i][j].Update();//�p�l����Counter������Ɍ�������o�O���������
		}
	}

	CheckPanicFlag();			//�p�j�b�N���(GameOver�̈����O)�̔���
}
//��Փx�C��
void CBlockMgr::Draw() {
							//�p�l���w�i�`��
	DrawRotaGraphF(300, 400, 1.0, 0.0, handleB, true);

							//�p�l���`��
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int k = Block[i][j].GetKind();//�u���b�N�̎�ނ������Ă���
			if (0 <= k && k < 6)				//�F����̏ꍇ	
			{
				Block[i][j].Draw(Handle[k]);
			}
			else if (GetAnotherKind(i, j) != AKnull)
			{
				switch (Block[i][j].GetAnotherKind())
				{
				case AKthree:
					Block[i][j].Draw(OjamaHandle[0]);//1*3
					break;
				case AKfour:
					Block[i][j].Draw(OjamaHandle[1]);//1*4
					break;
				case AKfive:
					Block[i][j].Draw(OjamaHandle[2]);//1*5
					break;
				case AKsix:
					Block[i][j].Draw(OjamaHandle[3]);//1*6
					break;
				case AKunchain:
					Block[i][j].Draw(OjamaHandle[4]);//2*6�Ƃ�
					break;
				default:break;
				}

			}
		}
	}
	Move.Draw();
	switch (DrawFlag)//�V�[��(0:�Q�[��,1:�p�j�b�N���,2:GameOver,3:Finish)
	{
	case 0:break;
	case 1:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), HandlePanic, true); break;
	case 2:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), HandleGameOver, true); break;
	case 3:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), Handle[3], true); break;
	default:
		break;
	}
}
///////////////���ז��p�ɏC��///////////////
void CBlockMgr::Gravity()//�F�Ŕ��f
{
	int keeping = 0;
	int cnt = 0;	//�����Ă�̂��Ȃ��Ȃ�܂ŌJ��Ԃ��B
	for (int i = 0; i < 6; i++)
	{
		for (int j = 14; j >= 5; j--)			
		{
			if (Block[i][j].GetKind() == 6)	//�󔒂ł���
			{
				if(keeping == 0)keeping = j;//(���ז��ł����Ă��H)��ԉ��̋󔒂̍��W���L�[�v
				else if (Block[i][j].GetIsOjama() == true) {
					keeping = 0;
				}
				else {}
			}
			else 			//�p�l��������
			{
				if (keeping != 0)					//�p�l���������āA�����Ă�ꍇ
				{
					for (int k = keeping; k > 5; k--)	//��ԉ��̋󔒂̍��W��ׂ��B
					{
						//��ނ݈̂ړ�
						int temp;
						bool tmp;
						temp = Block[i][k].GetKind();
						Block[i][k].SetKind(Block[i][k - 1].GetKind());	//�����Ȃ��Ƃ���˂�����ł���
						Block[i][k - 1].SetKind(temp);

						tmp = Block[i][k].GetFlag();
						Block[i][k].SetFlag(Block[i][k - 1].GetFlag());
						Block[i][k - 1].SetFlag(tmp);
						//��
					}
					cnt++;				//�����Ă�̂���������v���X
					break;				//���̗�͏I���
				}//���V
			}//��
			
		}//�c��
		keeping = 0;
	}//����
	if (cnt != 0)	//�����Ă�̂�����̂ŌJ��Ԃ��B
	{
		Gravity();	//�������
	}
}
////////////////���ז��p�ɏC�����ׂ��B///////
//��:Another->kind
void CBlockMgr::SwapBlock(int x,int y)//���E����
{
	int tmp;
	tmp = Block[x][y].GetKind();//kind -> color
	Block[x][y].SetKind(Block[x + 1][y].GetKind());
	Block[x+1][y].SetKind(tmp);
	tmp = Block[x][y].GetFlag();
	Block[x][y].SetFlag(Block[x + 1][y].GetFlag());
	Block[x + 1][y].SetFlag(tmp);
}

void CBlockMgr::CreateBlock() {		//�������p�l���������̋@�\
	for (int i = 0; i < 6; i++)	
	{
		Block[i][18].SetKind(GetRand(100000) % (g_nDifficult + 2));
	}
	CheckGameOver();
}

void CBlockMgr::DeleteBlock() {		//�s��
	//Block�̃N���X->exist��False�ɂ���R�[�h
	//Block->Setexist(False);
}

void CBlockMgr::CheckPanicFlag(){	//�p�j�b�N���(GameOver��O)�̔���
									//�Q�[���͈͊O�𒴂�����gameover
	bool Num = false;
	for (int i = 0; i < 6; i++)
	{
		if (Block[i][6].GetKind() != 6)		//(�ŏ�s-1)�Ƀp�l������������A
		{
			Num = true;//�p�j�b�N���
		}
		else if (Block[i][6].GetIsOjama() == true)//���ז��ł��A
		{
			Num = true;//�p�j�b�N���
		}
	}
	if (Num  == true)			//�p�j�b�N���
	{
		DrawFlag = 1;
	}
	else
	{
		DrawFlag = 0;
	}
}

void CBlockMgr::CheckGameOver()	//DrawFlag (0:����,1:�p�j�b�N���,2:�Q�[���I�[�o�[,3:Finish)
{
	//�p�j�b�N��ԂŃp�l���������s��ꂽ��Q�[���I�[�o�[
	if (DrawFlag == 1)
	{
		DrawFlag = 2;
		flag = true;
	}
}
//��Փx�C�������B
void CBlockMgr::BlockInitializer(int y1, int y2)	//�u���b�N���ŏ���������Ȃ��悤�ɔz�u����B
{
	int KindB[7] = { 0 };				//���ƂȂ�F ��Փx�I������Q�Ƃ�����
	bool CntFlag = true;
	bool Initing = true;
	int Num = 0;

	while (Initing == true && Num < 100)		//100��ȏ�͌J��Ԃ��Ȃ��B
	{
		CntFlag = false;
		Initing = false;
		for (int j = y1; j < y2; j++)		//y2�͊�{19
		{
			for (int i = 2; i < 6; i++)		//�����瑖��
			{
				switch (g_nDifficult)
				{
				case 1:			//���񂽂�
					for (int s = 0; s < 3; s++)		//�Z�A���A���̌���1�ɂ���B
					{
						KindB[s] = 1;
					}
					break;
				case 2:			//�ӂ�
					for (int s = 0; s < 4; s++)		//�Z�A���A���A���̌���1�ɂ���B
					{
						KindB[s] = 1;
					}
					break;
				case 3:			//���
					for (int s = 0; s < 5; s++)		//�n�[�g�A�Z�A���A���A���̌���1�ɂ���B
					{
						KindB[s] = 1;
					}
					break;
				case 4:			//�����Y
					for (int s = 0; s < 6; s++)		//�n�[�g�A�Z�A���A���A���A���̌���1�ɂ���B
					{
						KindB[s] = 1;
					}
				default:
					break;
				}
				
				if (Block[i][j].GetKind() < 6)		//������p�l���̎�
				{
					if (Block[i - 2][j].GetKind() == Block[i - 1][j].GetKind()		//���̑���
						&& Block[i - 1][j].GetKind() == Block[i][j].GetKind())
					{
						KindB[Block[i][j].GetKind()] = 0;
						CntFlag = true;
					}
					if (j > 1 && y1 < 17)											//�c�̑���
					{
						if (Block[i][j - 2].GetKind() == Block[i][j - 1].GetKind()
							&& Block[i][j - 1].GetKind() == Block[i][j].GetKind())
						{
							KindB[Block[i][j].GetKind()] = 0;
							CntFlag = true;
						}
					}
					int k;
					while (CntFlag == true)		//&& Block[i][j].GetKind() < 6
					{
						k = GetRand(100000) % (g_nDifficult + 2);
						if (KindB[k] == 1)
						{
							Block[i][j].SetKind(k);
							CntFlag = false;
							Initing = true;
							break;
						}
					}
				}
			}
		}
		Num++;
	}
	if (y1 < 17)
	{
		//printfDx("\n �p�l���̍ق�%d�񑱂��܂����B\n", Num);
	}
}

//���ז�����	
void CBlockMgr::MakeOjama(int i, int j ,CAnotherKind AnotherKind)//(���W�A���W�A���)
{

	//AnotherKind�̃Z�b�g
	Block[i][j].SetAnotherKind(AnotherKind);


	switch (AnotherKind)		//�����̒l�ɂ����
	{									//����Flag��true�ɂ���
	case AKnull:	break;
	case AKthree:
		for (int p = i; p < i + 3; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojama�ł���
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojama�ł���
		}
		break;
	case AKfive:
		for (int p = i; p < i + 5; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojama�ł���
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojama�ł���
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojama�ł���
		}
		break;
	default:
		break;
	}
}
