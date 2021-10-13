#pragma once

#include "DxLib.h"
#include <vector>
#include "Move.h"
#include "Block.h"
#include <time.h>
#include "define.h"



enum {		//�p�l���̎��	()
	eRed,
	eBlue,
	eGreen,
	eCyan,
	eYellow,
	ePurple,
	eBlank
};

class CBlockMgr
{
	int Handle[6];						//�摜�n���h��
	int OjamaHandle[5];
	std::vector<CBlock> Block[6];		//6*20�̃p�l���z�񐶐�

	CMove  Move;
	int handleB;						//�摜�n���h��

	int HandleClear;					//�摜�n���h��
	int HandleGameOver;					//�摜�n���h��
	int HandlePanic;					//�摜�n���h��

	int Counter;						//�R���g���[���[���猻�݂̎��Ԃ𓾂�s

	bool flag = false;		//Game�I�� �t���O
	int cnt = 0;
	int DrawFlag = 0;		//(0:����,1:�p�j�b�N���,2:gameover,3:Finish

	void CheckPanicFlag();
	void CheckGameOver();

public:
	CBlockMgr();
	~CBlockMgr();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();


	void CreateBlock();//x,y,���,����
	void DeleteBlock();


	void Gravity();		//������AMove�Ɉړ�����
	void SwapBlock(int x, int y);
	
	void BlockInitializer(int y1, int y2);		//�u���b�N�̔z�u��I�� ����:�㉺�͈̔�
												//��ڂ͊�{19�B
	void MakeOjama(int i, int j ,CAnotherKind AnotherKind);

	//�Q�[���I������
	inline bool GetFlag() { return flag; }

	void UpLiftDraw(double Uy) {
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				Block[i][j].UpLiftDraw(Uy);
			}
		}
	}

	inline CBlockMgr *GetThisPtr() { return this; }//�������g��n���B
	/*
	inline std::vector<CBlock> *GetBlockPtr() {		//���ɓ����Ă���p�l�����o���B
		std::vector<CBlock> *p = &Block[0];
		std::vector<CBlock> **pp = &p;
		*pp = &Block[0];
		return p; }
		*/

	inline std::vector<CBlock> *GetBlockPtr() {return Block;}

	inline int GetBlockKind(int x, int y) { return Block[x][y].GetKind();}
	inline bool GetBlockFlag(int x, int y) { return Block[x][y].GetFlag();}
	inline void SetBlockFlagTrue (int x, int y) {Block[x][y].SetFlag(true); }
	inline void SetBlockFlagFalse(int x, int y) { Block[x][y].SetFlag(false); }
	inline void SetBlockKind(int x, int y, int kind) {Block[x][y].SetKind(kind);}
	
	//���ז��p
	inline CAnotherKind GetAnotherKind(int x, int y) { return Block[x][y].GetAnotherKind(); };
	inline void SetAnotherKind(int x, int y, CAnotherKind Anotherkind) { Block[x][y].SetAnotherKind(Anotherkind); }
	
	inline void SetIsOjama(int i, int j, bool isojama) { Block[i][j].SetIsOjama(isojama); }
	inline int GetIsOjama(int i, int j) { return Block[i][j].GetIsOjama(); }

		////�X�R�A�A�^�b�N�p////
	inline int GetBlockCounter(int x, int y) { return Block[x][y].GetCounter(); }
	inline void SetBlockCounter(int x, int y, int Counter) { Block[x][y].SetCounter(Counter); }
	
	inline void ReduceBlockCounter(int x, int y) {
		int cnt = 0;
		cnt = Block[x][y].GetCounter();
		cnt--;
		Block[x][y].SetCounter(cnt);
	}

	inline int GetBlockStop(){ return DrawFlag; }	//�R���g���[���[�ɃQ�[���̏�Ԃ�`����

	inline void SetGameFinishFlag() { DrawFlag = 3; flag = true; }		//�Q�[���I��+Finish
	
	//inline std::array<CBlock , 10> *GetBlockPtr() { return &Block; }
};



//(1)...�폜���ꂽ�֐����Q�Ƃ��悤�Ƃ��Ă��܂�
//(2)...�N���X�^���K�v�ł�=�N���X�ƌ��Ȃ���Ă��Ȃ�