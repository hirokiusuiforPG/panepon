#pragma once
#include "DxGraphic.h"


// アニメーションクラス
class DxAnimation
{

private :

	const	DxGraphic*		pGraphicClass;				// 取り扱いグラフィッククラスへのポインタ

	int				NowFrame;					// 現在のフレーム
	int				NextStep;					// 次へのステップ数 
	int				NowStep;					// 現在のステップ数
	bool			RepeatFlag;					// リピートフラグ
	GraphicData_PTR	pGraphic;					// 画像データへのポインタ

public :

	void			Release( void );				// 解放
	int				DoStep( int step );				// ステップ進行
	bool			CheckEnd( void )	const;		// チェック_再生終了
	
	// リピートフラグ
	void			SetRepeatFlag( bool repeat );	// 設定
	bool			GetRepeatFlag( void )	const;	// 取得

	void			ToFirst( void );				// 最初へ戻る
	void			ToEnd( void );					// 最後まで行く

	// 設定_現在のフレーム
	int				SetFrameNumber( int frameNumber, bool stepResetFlag );

	// 取得_現在のフレーム
	int				GetFrameNumber( void )	const;

	// 設定_次までのステップ数
	int				SetNextStep( int stepNumber );

	// 取得_次までのステップ数
	int				GetNextStep( void )	const;

	// グラフィックハンドル取得
	int				GetHandle( void )	const;

	// グラフィッククラスへのポインタの設定
	void			SetGraphic(	const	DxGraphic* pGraphicClass );

	// 代入処理
	DxAnimation& operator = (const DxAnimation& another);

	// コンストラクタ、デストラクタ
	DxAnimation();
	DxAnimation( GraphicData_PTR graphic_ptr );
	DxAnimation( DxGraphic* pGraphicClass );
	//~DxAnimation();

} ;
