
#include "DxGraphic.h"

/**************************************************************
 *	グラフィック数
 **************************************************************
 *	イメージ数を取得
 **************************************************************
 *	引数：	
 *	-> なし
 *
 *	戻り値:
 *	int
 *	->	個数
 *
 *************************************************************/
int	DxGraphic::GetNumber( void )	const
{
	return HandleArray.size();
}

/**************************************************************
 *	取得_グラフィックハンドル
 **************************************************************
 *	取得_グラフィックハンドル
 **************************************************************
 *	引数：	
 *
 *	int number
 *	->	要素番号
 *
 *	戻り値:
 *	->	int ハンドル
 *	->	エラー	0
 *
 *************************************************************/
int	DxGraphic::GetHandle( int number )	const
{
	if( number < 0 || ( int ) HandleArray.size() <= number )
		return 0;
	return HandleArray[ number ].Handle;
}

/**************************************************************
 *	解放関数
 **************************************************************
 *	画像の解放
 **************************************************************
 *	引数：	
 *	->	なし
 *
 *	戻り値:
 *	->	なし
 *
 *************************************************************/
void DxGraphic::Release( void )
{
	// 解放
	for( vector< GraphicData >::iterator it = HandleArray.begin(); it != HandleArray.end(); it ++ )
	{
		if( it->BorrowedFlag == 0 )
			DeleteGraph( it->Handle );
	}
	HandleArray.clear();
}

/**************************************************************
 *	描画関数
 **************************************************************
 *	描画
 **************************************************************
 *	引数：	
 *		
 *	XY< int > xy
 *	->	座標
 *
 *	int transFlag
 *	->	透過フラグ
 *	
 *	int number
 *	->	番号
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int	DxGraphic::Draw( XY< int > xy, int transFlag, int number )
{
	return this->Draw( xy.X, xy.Y, transFlag, number );
}

/**************************************************************
 *	描画関数
 **************************************************************
 *	描画
 **************************************************************
 *	引数：	
 *		
 *	int x, int y
 *	->	座標
 *
 *	int transFlag
 *	->	透過フラグ
 *	
 *	int number
 *	->	番号
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int	DxGraphic::Draw( int x, int y, int transFlag, int number )
{
	if( number < 0 || ( int ) HandleArray.size() <= number )
		return -1;
	return DrawGraph( x, y, HandleArray[ number ].Handle, transFlag );
}

/**************************************************************
 *	受け取り_グラフィックハンドル
 **************************************************************
 *	借り物フラグを立てる
 **************************************************************
 *	引数：	
 *		
 *	const char* filePath
 *	->	画像パス
 *
 *	int numAll, XY< int > num
 *	->	全体の個数と座標系に対しての分割個数
 *	
 *	XY< int > size
 *	->	サイズ
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int	DxGraphic::CatchHandle( int handle )
{	
	GraphicData	graphic;
	int			sizeX, sizeY;
	if( handle == -1 )
		return -1;

	if( GetGraphSize( handle, &sizeX, &sizeY ) == -1 )
		return -1;

	graphic.Handle = handle;
	graphic.Size.Set( sizeX, sizeY );

	HandleArray.push_back( graphic );

	return 0;
}

/**************************************************************
 *	分割画像を読み込み
 **************************************************************
 *	ひとつの画像を分割読み込みし、グラフィックリストにプッシュする。
 **************************************************************
 *	引数：	
 *		
 *	const char* filePath
 *	->	画像パス
 *
 *	int numAll, XY< int > num
 *	->	全体の個数と座標系に対しての分割個数
 *	
 *	XY< int > size
 *	->	サイズ
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int	DxGraphic::LoadDiv( const char* filePath, int numAll, XY< int > num, XY< int > size )
{
	return this->LoadDiv( filePath, numAll, num.X, num.Y, size.X, size.Y );
}

/**************************************************************
 *	分割画像を読み込み
 **************************************************************
 *	ひとつの画像を分割読み込みし、グラフィックリストにプッシュする。
 **************************************************************
 *	引数：	
 *		
 *	const char* filePath
 *	->	画像パス
 *
 *	int numAll, int numX ,int numY
 *	->	全体の個数と座標系に対しての分割個数
 *	
 *	int sizeX, int sizeY
 *	->	サイズ
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int	DxGraphic::LoadDiv( const char* filePath, int numAll, int numX, int numY, int sizeX, int sizeY )
{
	GraphicData	graphic;
	int			*handle;
	
	handle = new int[ numAll ];
	if( handle == NULL )
		return -1;

	// 読み込み
	if( LoadDivGraph( filePath, numAll, numX, numY, sizeX, sizeY, handle ) == -1 )
		return -1;

	for( int i = 0; i < numAll; i ++ )
	{
		int			iSizeX, iSizeY;

		// サイズ取得
		if( GetGraphSize( handle[ i ], &iSizeX, &iSizeY ) == -1 )
		{
			// 失敗
			for( ; i >= 0; i -- )
				DeleteGraph( handle[ i ] );		
			delete[] handle;
			return -1;
		}

		// 設定
		graphic.Handle = handle[ i ];
		graphic.Size.Set( iSizeX, iSizeY );

		// プッシュ
		HandleArray.push_back( graphic );
	}

	// 成功
	return 0;
}

/**************************************************************
 *	画像を読み込み
 **************************************************************
 *	画像を読み込み、
 *	そのグラフィックハンドルの情報を画像情報保持構造体へ入れ、
 *	グラフィックリストにプッシュする。
 **************************************************************
 *	引数：	
 *		
 *	const char* filePath
 *	->	画像パス
 *
 *	戻り値:
 *	0	成功
 *	-1	失敗
 *
 *************************************************************/
int DxGraphic::Load( const char* filePath )
{
	GraphicData	graphic;
	int			handle;
	int			sizeX, sizeY;

	// 読み込み
	handle = LoadGraph( filePath );
	if( handle == -1 )
		return -1;

	// サイズ取得
	if( GetGraphSize( handle, &sizeX, &sizeY ) == -1 )
	{
		DeleteGraph( handle );
		return -1;
	}

	// 設定
	graphic.Handle = handle;
	graphic.Size.Set( sizeX, sizeY );

	// プッシュ
	HandleArray.push_back( graphic );

	// 成功
	return 0;
}

/**************************************************************
 *	コンストラクタ
 **************************************************************
 *	初期処理を行う
 **************************************************************
 *	引数：	
 *		なし
 *
 *************************************************************/
DxGraphic::DxGraphic()
{
}

/**************************************************************
 *	デストラクタ
 **************************************************************
 *	後処理を行う
 *	画像の解放
 **************************************************************
 *	引数：	
 *		なし
 *
 *************************************************************/
DxGraphic::~DxGraphic()
{
	this->Release();
}