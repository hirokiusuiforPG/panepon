#pragma once

#include"Choices.h"

//コンストラクタ（XYサイズ、個数）
Choices::Choices( XY<int> size , int num )
{
	Size = size;
	ItemNumber = num;
	
	NowItem.X = 0;
	NowItem.Y = 0;
	LFJumpFlag = true;
	LRJumpFlag = true;
	UDJumpFlag = true;
}

//コンストラクタ（Xサイズ、Yサイズ、個数）
Choices::Choices( int sizeX , int sizeY , int num )
{
	Size.Set( sizeX , sizeY );
	ItemNumber = num;

	NowItem.X = 0;
	NowItem.Y = 0;
	LFJumpFlag = true;
	LRJumpFlag = true;
	UDJumpFlag = true;
}

//選択肢を回数分だけ横に操作する（左：マイナス、右：プラス）　操作後のX座標を返す
int Choices::HorizontalMove( int number )
{
	int i;
	int seqIndex;

	//正の値の場合（右に回す）
	if ( number > 0 )
	{
		for ( i = 0; i < number; i++ )
		{
			seqIndex = NowItem.Y * Size.X + NowItem.X;

			//右端に到達していない
			if (NowItem.X < Size.X - 1 && seqIndex < ItemNumber - 1)
			{
				NowItem.X++;
			}
			//右端に到達した
			else
			{
				//境界値でのジャンプフラグがONだったら、最前の項目に戻る
				if (LRJumpFlag)
				{
					NowItem.X = 0;
				}
			}
		}
	}
	//負の値の場合（左に回す）
	else
	{
		number = abs( number );

		for ( i = 0; i < number; i++ )
		{
			//左端に到達していない
			if ( NowItem.X > 0 )
			{
				NowItem.X--;
			}
			//左端に到達した
			else
			{
				//境界値でのジャンプフラグがONだったら、ジャンプする
				if (LRJumpFlag)
				{
					seqIndex = NowItem.Y * Size.X + NowItem.X;
					while (NowItem.X < Size.X - 1 && seqIndex < ItemNumber - 1)
					{
						NowItem.X++;
						seqIndex = NowItem.Y * Size.X + NowItem.X;
					}
				}
				
			}
		}
	}

	return NowItem.X;
}

//選択肢を回数分だけ縦に操作する（上：マイナス、下：プラス）　操作後のY座標を返す
int Choices::VerticalMove( int number )
{
	int i , seqIndex;

	//正の値の場合（下に回す）
	if ( number > 0 )
	{
		for ( i = 0; i < number; i++ )
		{
			seqIndex = NowItem.Y * Size.X + NowItem.X;

			if (seqIndex + Size.X < ItemNumber)
			{
				NowItem.Y++;
			}
			else
			{
				//境界値でのジャンプフラグがONだったら、ジャンプする
				if ( UDJumpFlag )
				{
					NowItem.Y = 0;
				}
			}
		}
	}
	//負の値の場合（上に回す）
	else
	{
		number = abs( number );

		for ( i = 0; i < number; i++ )
		{
			if ( NowItem.Y > 0 )
			{
				NowItem.Y--;
			}
			else
			{
				//境界値でのジャンプフラグがONだったら、ジャンプする
				if ( UDJumpFlag )
				{
					seqIndex = (NowItem.Y + 1) * Size.X + NowItem.X;
					while (seqIndex < ItemNumber)
					{
						NowItem.Y++;
						seqIndex = (NowItem.Y + 1) * Size.X + NowItem.X;
					}
				}
			}
		}
	}

	return NowItem.Y;
}

//選択肢を回数分だけ進める　プラスの場合右に進み、一番右の項目から進む時、一つ下の一番左の項目へ移る　マイナスの場合、左に進み、一番左の項目から進む場合、一つ上の一番右の項目へ移る
void Choices::AheadMove( int number )
{
	int i;
	int seqIndex;

	//正の値の場合（右に進む、一番右までいったら一つ下の左端に戻る）
	if ( number > 0 )
	{
		for ( i = 0; i < number; i++ )
		{
			seqIndex = NowItem.Y * Size.X + NowItem.X;
			if (NowItem.X < Size.X - 1 && seqIndex < ItemNumber - 1)
			{
				NowItem.X++;
			}
			else
			{
				//一つ下の左端に戻る
				if (seqIndex + 1 < ItemNumber)
				{
					NowItem.Y++;
					NowItem.X = 0;
				}
				else
				{
					//境界値でのジャンプフラグがONだったら、ジャンプする
					if ( LFJumpFlag )
					{
						NowItem.X = 0;
						NowItem.Y = 0;
					}
				}

			}
		}
	}
	else
	{
		number = abs( number );

		for ( i = 0; i < number; i++ )
		{
			if ( NowItem.X > 0 )
			{
				NowItem.X--;
			}
			else
			{
				//一つ上の右端に戻る
				if ( NowItem.Y > 0 )
				{
					NowItem.Y--;
					NowItem.X = Size.X - 1;
				}
				else
				{
					//境界値でのジャンプフラグがONだったら、ジャンプする
					if ( LFJumpFlag )
					{
						NowItem.X = (ItemNumber - 1) % Size.X;
						NowItem.Y = (ItemNumber - 1) / Size.X;
					}
				}
			}
		}
	}
}

//選択項目を指定の項目へと移す
int Choices::SetItem( int x , int y )
{
	int ret;

	if ( ( x > 0 ) && ( x < Size.X) && ( y > 0 ) && ( y < Size.Y ) )
	{
		NowItem.Set( x , y );
		ret = 0;
	}
	else
	{
		ret = -1;
	}

	return ret;
}

//選択項目を指定の項目へと移す
int Choices::SetItem( XY<int> xy )
{
	int ret;

	if ( ( xy.X > 0 ) && ( xy.X < Size.X) && ( xy.Y > 0 ) && ( xy.Y < Size.Y ) )
	{
		NowItem.Set( xy.X , xy.Y );
		ret = 0;
	}
	else
	{
		ret = -1;
	}

	return ret;
}

//選択中の項目の座標を返す
XY<int> Choices::GetItem()
{
	return NowItem;
}

//選択中の項目の座標を返す
int Choices::GetItemX()
{
	return NowItem.X;
}

//選択中の項目の座標を返す
int Choices::GetItemY()
{
	return NowItem.Y;
}