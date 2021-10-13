#pragma once
#include "XandY.h"


// �摜���ێ��\����
typedef struct tagGraphicData
{

	int					Handle;			// �n���h��
	bool				BorrowedFlag;	// �؂蕨�ӂ炮
	XY< int >			Size;			// �摜�T�C�Y

	// ������
	tagGraphicData()
	{
		Handle = 0;
		BorrowedFlag = false;
		Size.Set( 0, 0 );
	}

	tagGraphicData( int handle, bool borrowed_flag, XY< int > size )
	{
		Handle = handle;
		BorrowedFlag = borrowed_flag;
		Size = size;
	}

} GraphicData, *GraphicData_PTR;