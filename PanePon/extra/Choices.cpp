#pragma once

#include"Choices.h"

//�R���X�g���N�^�iXY�T�C�Y�A���j
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

//�R���X�g���N�^�iX�T�C�Y�AY�T�C�Y�A���j
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

//�I�������񐔕��������ɑ��삷��i���F�}�C�i�X�A�E�F�v���X�j�@������X���W��Ԃ�
int Choices::HorizontalMove( int number )
{
	int i;
	int seqIndex;

	//���̒l�̏ꍇ�i�E�ɉ񂷁j
	if ( number > 0 )
	{
		for ( i = 0; i < number; i++ )
		{
			seqIndex = NowItem.Y * Size.X + NowItem.X;

			//�E�[�ɓ��B���Ă��Ȃ�
			if (NowItem.X < Size.X - 1 && seqIndex < ItemNumber - 1)
			{
				NowItem.X++;
			}
			//�E�[�ɓ��B����
			else
			{
				//���E�l�ł̃W�����v�t���O��ON��������A�őO�̍��ڂɖ߂�
				if (LRJumpFlag)
				{
					NowItem.X = 0;
				}
			}
		}
	}
	//���̒l�̏ꍇ�i���ɉ񂷁j
	else
	{
		number = abs( number );

		for ( i = 0; i < number; i++ )
		{
			//���[�ɓ��B���Ă��Ȃ�
			if ( NowItem.X > 0 )
			{
				NowItem.X--;
			}
			//���[�ɓ��B����
			else
			{
				//���E�l�ł̃W�����v�t���O��ON��������A�W�����v����
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

//�I�������񐔕������c�ɑ��삷��i��F�}�C�i�X�A���F�v���X�j�@������Y���W��Ԃ�
int Choices::VerticalMove( int number )
{
	int i , seqIndex;

	//���̒l�̏ꍇ�i���ɉ񂷁j
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
				//���E�l�ł̃W�����v�t���O��ON��������A�W�����v����
				if ( UDJumpFlag )
				{
					NowItem.Y = 0;
				}
			}
		}
	}
	//���̒l�̏ꍇ�i��ɉ񂷁j
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
				//���E�l�ł̃W�����v�t���O��ON��������A�W�����v����
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

//�I�������񐔕������i�߂�@�v���X�̏ꍇ�E�ɐi�݁A��ԉE�̍��ڂ���i�ގ��A����̈�ԍ��̍��ڂֈڂ�@�}�C�i�X�̏ꍇ�A���ɐi�݁A��ԍ��̍��ڂ���i�ޏꍇ�A���̈�ԉE�̍��ڂֈڂ�
void Choices::AheadMove( int number )
{
	int i;
	int seqIndex;

	//���̒l�̏ꍇ�i�E�ɐi�ށA��ԉE�܂ł����������̍��[�ɖ߂�j
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
				//����̍��[�ɖ߂�
				if (seqIndex + 1 < ItemNumber)
				{
					NowItem.Y++;
					NowItem.X = 0;
				}
				else
				{
					//���E�l�ł̃W�����v�t���O��ON��������A�W�����v����
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
				//���̉E�[�ɖ߂�
				if ( NowItem.Y > 0 )
				{
					NowItem.Y--;
					NowItem.X = Size.X - 1;
				}
				else
				{
					//���E�l�ł̃W�����v�t���O��ON��������A�W�����v����
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

//�I�����ڂ��w��̍��ڂւƈڂ�
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

//�I�����ڂ��w��̍��ڂւƈڂ�
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

//�I�𒆂̍��ڂ̍��W��Ԃ�
XY<int> Choices::GetItem()
{
	return NowItem;
}

//�I�𒆂̍��ڂ̍��W��Ԃ�
int Choices::GetItemX()
{
	return NowItem.X;
}

//�I�𒆂̍��ڂ̍��W��Ԃ�
int Choices::GetItemY()
{
	return NowItem.Y;
}