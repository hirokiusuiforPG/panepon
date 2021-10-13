#pragma once
#include "DxLib.h"
#include "GraphicData.h"

#include <vector>
using namespace std;


// グラフィッククラス
class DxGraphic
{

private :

	vector< GraphicData >	HandleArray;			// グラフィックリスト

public :

	// 画像を読み込み
	int					Load( const char* filePath );

	// 分割読み込み
	int					LoadDiv( const char* filePath, int numAll, int numX, int numY, int sizeX, int sizeY );
	int					LoadDiv( const char* filePath, int numAll, XY< int > num, XY< int > size );
	
	// 受け取り_グラフィックハンドル
	int					CatchHandle( int handle );

	// 描画
	int					Draw( int x, int y, int transFlag, int number = 0 );
	int					Draw( XY< int > xy, int transFlag, int number = 0 );

	// 画像の解放
	void				Release( void );

	// 取得_グラフィックハンドル
	int					GetHandle( int number = 0 )	const;

	// 取得_画像個数
	int					GetNumber( void )	const;
		
	// コンストラクタ、デストラクタ
	DxGraphic();
	~DxGraphic();

} ;