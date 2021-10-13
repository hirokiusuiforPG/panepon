#pragma once

#include "Cursor.h"
#include "BlockMgr.h"
#include "DeleteDecide.h"
#include "Rule.h"
#include "board.h" 

class CController
{
	CCursor			Cursor;
	CBlockMgr		BlockMgr;
	CDeleteDecide	DeleteDecide;

	CRule			Rule;

	int Handle1;		//�w�i
	int Handle2;		//�w�i
	int Handle3;		//�B��
	int Handle4;		//�B��

	int soundflag;
	
	int Timer;		//����グ�Ɏg���B UpLift();
	int UpLiftCnt;	//�p�l���̂���グ�Ɏg�� 25���1�p�l����

	int Paneltop[6];

	bool ComboFlag;		//Combo()�ł���
	int ComboNum;		//Combo()�Ŏg��
	bool DeletingFlag;	//�폜����������true

	int ScorePoint;		//Score,rule�Ŏg��

	struct HSP {					//���Z���̃X�R�A��\��
		int point;					//���_
		int DrawTime;				//�\������
		bool Flag;					//
	};

	int CheckPanic;	//���̏�ԂŃp�l�����P�����肠�����GameOver

	int ScoreCounter;

	int StageTime;

	////GameOver���////
	int Cr;
	int GameEnd;		//���̒l�ɂ���Ď��̃V�[�������肷��B
	int  Font00 = CreateFontToHandle(NULL, 30, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	int  Font01 = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 2);
	int  pointer = 420;
	//////////////////
	bool PauseMode;
	bool X_ButtonMode;		//x�{�^���ł���グ

	void SwapBlock();
	int Search();
	void Delete();
	void Combo();

	void UpLift1();
	void UpLift2();

	void AddScore();

	void GameOver();

	void Pause();

	void TimeProcess();

	void X_button();			//x�{�^���ł���グ

	void OjamaGravity();
	void OjamaPanelTop();
	void OjamaChange();
	void OjamaMakePanel(int i, int j, CAnotherKind Anotherkind);	//���ז����p�l���ɕϊ�

	void OjamaPush();//���ז�����
	
	void SetOjama(int i, int j, CAnotherKind AnotherKind, bool flag);//���ז��t���O���Z�b�g����B

public:
	CController();
	~CController();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//inline bool CheckGameEnd() { return EnemyMgr.GetFlag(); }
	//�G��|�����ꍇ	<vs COM>

	//inline bool CheckGameEnd() { return BlockMgr.GetFlag(); }
	//��ʏ㕔�܂Ńp�l���������ꍇ

	inline bool CheckGameEnd1() { return Rule.CheckGameEnd(); }
	//���Ԑ؂�
	inline bool CheckGameEnd2() { return BlockMgr.GetFlag(); }
	//��ʏ㕔�܂Ńp�l���������ꍇ

	inline int CheckGameEnd3() { return GameEnd; }
};