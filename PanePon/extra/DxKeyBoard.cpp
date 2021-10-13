#pragma once
#include"DxKeyBoard.h"
#include"DxLib.h"

//コンストラクタ
DxKeyBoard::DxKeyBoard()
{
	int i = 0;

	//変数の初期化
	for (i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
		OldKeyState[i] = 0;
		KeepTime[i] = 0;
	}
}

//キー情報をリセット（全て0）にする
void DxKeyBoard::ResetKeyData()
{
	int i;

	//変数の初期化
	for (i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
		OldKeyState[i] = 0;
		KeepTime[i] = 0;
	}
}

//状態を更新する
void DxKeyBoard::UpDate()
{
	int i;

	//現フレームの状態を前フレームの状態として保持する
	for (i = 0; i < 256; i++)
	{
		OldKeyState[i] = KeyState[i];
	}

	//現フレームの状態を更新
	GetHitKeyStateAll(KeyState);

	//ボタン押下維持状態の更新
	for (i = 0; i < 256; i++)
	{
		if (KeyState[i] != OldKeyState[i])
		{
			KeepTime[i] = 0;
		}
		else
		{
			KeepTime[i]++;
		}
	}
}

//指定したキーが押されているかどうか　キー情報配列の添え字をkeyCodeにしたものを返す
//エラーならばfalseを返す true押されている false押されていない
bool DxKeyBoard::CheckPress(int keyCode)	const
{
	bool ret = false;

	if (keyCode < 256)
	{
		if (KeyState[keyCode] == 1)
		{
			ret = true;
		}
	}

	return ret;
}

//前フレームのキー情報と現在のキー情報を比べ、指定したキーが押された瞬間かどうかを調べる
//エラーならば、falseを返す
bool DxKeyBoard::CheckPressMoment(int keyCode)	const
{
	if (KeyState[keyCode] - OldKeyState[keyCode] > 0)
		return true;
	else
		return false;
}

//前フレームのキー情報と現在のキー情報を比べ指定したキーが離された瞬間であるかどうかを調べる
//エラーならば、falseを返す
bool DxKeyBoard::CheckFreeMoment(int keyCode)	const
{
	if (KeyState[keyCode] - OldKeyState[keyCode] < 0)
		return true;
	else
		return false;
}

//指定したキーが現在の押下状態を何フレーム維持しているのかを取得する
//keyCodeが不正ならば、0を返す
int DxKeyBoard::GetTime(int keyNumber)	const
{
	if (keyNumber < 256)
	{
		return KeepTime[keyNumber];
	}
	else
	{
		return 0;
	}
}