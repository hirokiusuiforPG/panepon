#include "Search.h"

CSearch::CSearch() {			//Cursor�͂���Ȃ�
}

CSearch::~CSearch()
{
}



void CSearch::Initialize()	
{
}

void CSearch::Update()							
{					
}
//���̒l������Ɨ\�z���ăR�[�h������
int CSearch::CheckSearchBlock(int kind1, int kind2)
{
	if (kind1 == kind2)
	{
		return kind1;		//�����F
	}
	else
	{
		return -1;
	}
}
/*
int CSearch::CheckSearchBlock(int kind1, int kind2)
{

	int i , j;	//�c��
	int k;		//j�̏����l
	int Num;	//�����F���A���ő����Ă��邩�ǂ���
	
	for (i = 0; i < 6; i++)
	{
		k = 5;			//�c�����ʒu
		Num = 0;
		for (j = 5; j < 14; j++)
		{
			if (Block[i][k].GetKind() == Block[i][j].GetKind())	//�����ʒu�̃u���b�N�ƌ��ݒn�̐F���r
			{
				if (Block[i][j].GetKind() != 6)	//�󔒂łȂ�������
				{
					Num++;
				}
			}
			else
			{
				if (Num >= 3)
				{
					for (; k != j; k++)
					{
						Block[i][k].SetFlag(true);
					}
				}
							//�R���ȏ㑱���Ă��Ȃ�������B
				Num = 0;
				k = j;		//�����Ȃ��Ă�����
			}
		}
		if (Num >= 3)
		{
			for (; k != j; k++)
			{
				Block[i][k].SetFlag(true);
			}
		}
	}

	for(j = 5; j < 14; j++)
	{
		k = 0;			//���@�����ʒu
		Num = 0;
		for (i = 0; i < 6; i++)
		{
			if (Block[k][j].GetKind() == Block[i][j].GetKind())	//�����ʒu�̃u���b�N�ƌ��ݒn�̐F���r
			{
				if (Block[i][j].GetKind() != 6)	//�󔒂łȂ�������
				{
					Num++;
				}
			}
			else
			{
				if (Num >= 3)
				{
					for (; k != i; k++)
					{
						Block[k][j].SetFlag(true);
					}
				}
				//else 3���� �������Ȃ�

				Num = 0;
				k = i;		//�����Ȃ��Ă�����
			}
		}
		if (Num >= 3)
		{
			for (; k != i; k++)
			{
				Block[k][j].SetFlag(true);
			}
		}
	}
}
*/

