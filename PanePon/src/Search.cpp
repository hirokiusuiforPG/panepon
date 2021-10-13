#include "Search.h"

CSearch::CSearch() {			//Cursorはいらない
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
//この値が来ると予想してコードを書く
int CSearch::CheckSearchBlock(int kind1, int kind2)
{
	if (kind1 == kind2)
	{
		return kind1;		//同じ色
	}
	else
	{
		return -1;
	}
}
/*
int CSearch::CheckSearchBlock(int kind1, int kind2)
{

	int i , j;	//縦横
	int k;		//jの初期値
	int Num;	//同じ色が連続で続いているかどうか
	
	for (i = 0; i < 6; i++)
	{
		k = 5;			//縦初期位置
		Num = 0;
		for (j = 5; j < 14; j++)
		{
			if (Block[i][k].GetKind() == Block[i][j].GetKind())	//初期位置のブロックと現在地の色を比較
			{
				if (Block[i][j].GetKind() != 6)	//空白でなかったら
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
							//３こ以上続いていなかったら。
				Num = 0;
				k = j;		//書かなくてもいい
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
		k = 0;			//横　初期位置
		Num = 0;
		for (i = 0; i < 6; i++)
		{
			if (Block[k][j].GetKind() == Block[i][j].GetKind())	//初期位置のブロックと現在地の色を比較
			{
				if (Block[i][j].GetKind() != 6)	//空白でなかったら
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
				//else 3個未満 何もしない

				Num = 0;
				k = i;		//書かなくてもいい
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

