#include "Delete.h"

//delete�ɕK�v�Ȃ̂�Block->GetFlag()��
//Block->SetExist()�B
//������Block->Deleting(�����Ă���r��)���K�v�ɂȂ邩���m��Ȃ��B

//�@�\
//Swap() -> search() -> delete() -> BlockMgr �� 
//Gravity() -> search() -> delete() -> BlockMgr�� �ʂ��č폜�v��������B(��Block���Ƃɗ��Ȃ��B)
//Effect��\�����Ă���Ԃ͑��݂͂��Ă���̂ŁADeleting���K�v�B
//Effect���I�������瑶�݂������B


CDelete::CDelete() {			//Cursor�͂���Ȃ�
	
}

CDelete::~CDelete()
{
}

void CDelete::Initialize()	//CCursor *Cursor �� CCursor *p �� * = * ��\���Ă���
{
}

void CDelete::Update()								//�p�l���S���ɍs��
{
	CheckDeleteBlock();								//update�ɒ��ڏ����Ă��ǂ������B
}

void CDelete::CheckDeleteBlock()
{
	/*	���e(����)
	for(int i = 0; i < 6; i++){						//vector��6�p�ӂ��Ă�B
		for(int j = 0; j < 19; j++){				//resize()�g����20�p�ӂ��Ă�B
			if(Block[i][j].GetFlag() == true){
													//������Effect������B ���͏u���Ƀp�l����������B
				Block[i][j].SetExist() == false;
			}
		}
	}*/
	/*
	//�Ԑ�									
	for (auto it1 = BlockMgr->GetBlockPtr()->begin(); it1 != BlockMgr->GetBlockPtr()->end(); it1++)
	{
		int t = 0;
		if (it1->GetFlag() == true)					//����G���[�͋N���Ȃ����s���ȓ�����������B
		{
			//printfDx("�\������Ă�B%d",t);		//�����œ���m�F
			t++;
		}
	}
	*/

}

	//8��19��  �f�o�b�N�o����悤�ɂ����B
