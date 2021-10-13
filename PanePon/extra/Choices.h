#pragma once

#include"XandY.h"

class Choices
{
protected:
	XY<int> Size;		//�{�^�����ǂ�ȃT�C�Y�Ŕz�u����Ă��邩
	int ItemNumber;		//�{�^���̍��v��
	XY<int> NowItem;	//���ǂ̍��ڂ�I�𒆂�

public:
	bool LRJumpFlag;	//(���E)���E�ƂȂ鍀�ڂōX�ɑ��삵���ۂɁA�擪�֖߂邩�ǂ����̃t���O
	bool UDJumpFlag;	//(�㉺)���E�ƂȂ鍀�ڂōX�ɑ��삵���ۂɁA�擪�֖߂邩�ǂ����̃t���O
	bool LFJumpFlag;	//(�O��)���E�ƂȂ鍀�ڂōX�ɑ��삵���ۂɁA�擪�֖߂邩�ǂ����̃t���O

	//�R���X�g���N�^�iXY�T�C�Y�A���j
	Choices( XY<int> , int );
	
	//�R���X�g���N�^�iX�T�C�Y�AY�T�C�Y�A���j
	Choices( int , int , int );

	//�I�������񐔕��������ɑ��삷��i���F�}�C�i�X�A�E�F�v���X�j�@������X���W��Ԃ�
	int HorizontalMove( int );
	
	//�I�������񐔕������c�ɑ��삷��i��F�}�C�i�X�A���F�v���X�j�@������Y���W��Ԃ�
	int VerticalMove( int );
	
	//�I�������񐔕������i�߂�@�v���X�̏ꍇ�E�ɐi�݁A��ԉE�̍��ڂ���i�ގ��A����̈�ԍ��̍��ڂֈڂ�@�}�C�i�X�̏ꍇ�A���ɐi�݁A��ԍ��̍��ڂ���i�ޏꍇ�A���̈�ԉE�̍��ڂֈڂ�
	void AheadMove( int );

	//�I�����ڂ��w��̍��ڂւƈڂ�
	int SetItem( int , int );

	//�I�����ڂ��w��̍��ڂւƈڂ�
	int SetItem( XY<int> );

	//�I�𒆂̍��ڂ̍��W��Ԃ�
	XY<int> GetItem();

	//�I�𒆂̍��ڂ�X���W��Ԃ�
	int GetItemX();

	//�I�𒆂̍��ڂ�Y���W��Ԃ�
	int GetItemY();
};