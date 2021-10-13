#pragma once

#include"XandY.h"

class Choices
{
protected:
	XY<int> Size;		//ボタンがどんなサイズで配置されているか
	int ItemNumber;		//ボタンの合計数
	XY<int> NowItem;	//今どの項目を選択中か

public:
	bool LRJumpFlag;	//(左右)境界となる項目で更に操作した際に、先頭へ戻るかどうかのフラグ
	bool UDJumpFlag;	//(上下)境界となる項目で更に操作した際に、先頭へ戻るかどうかのフラグ
	bool LFJumpFlag;	//(前後)境界となる項目で更に操作した際に、先頭へ戻るかどうかのフラグ

	//コンストラクタ（XYサイズ、個数）
	Choices( XY<int> , int );
	
	//コンストラクタ（Xサイズ、Yサイズ、個数）
	Choices( int , int , int );

	//選択肢を回数分だけ横に操作する（左：マイナス、右：プラス）　操作後のX座標を返す
	int HorizontalMove( int );
	
	//選択肢を回数分だけ縦に操作する（上：マイナス、下：プラス）　操作後のY座標を返す
	int VerticalMove( int );
	
	//選択肢を回数分だけ進める　プラスの場合右に進み、一番右の項目から進む時、一つ下の一番左の項目へ移る　マイナスの場合、左に進み、一番左の項目から進む場合、一つ上の一番右の項目へ移る
	void AheadMove( int );

	//選択項目を指定の項目へと移す
	int SetItem( int , int );

	//選択項目を指定の項目へと移す
	int SetItem( XY<int> );

	//選択中の項目の座標を返す
	XY<int> GetItem();

	//選択中の項目のX座標を返す
	int GetItemX();

	//選択中の項目のY座標を返す
	int GetItemY();
};