#pragma once
#include "XandY.h"


// 画像情報保持構造体
typedef struct tagGraphicData
{

	int					Handle;			// ハンドル
	bool				BorrowedFlag;	// 借り物ふらぐ
	XY< int >			Size;			// 画像サイズ

	// 初期化
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