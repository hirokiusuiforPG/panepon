#pragma once
#include"DxJoyPad.h"
#include"DxLib.h"

//コンストラクタ
DxJoyPad::DxJoyPad()
{
	KeyState = 0;
	OldKeyState = 0;

	//ジョイパッドの接続を確認し、入力を設定する
	if (GetJoypadNum() > 0)
	{
		InputType = DX_INPUT_PAD1;
		ErrorFlag = false;
	}
	else
	{
		InputType = 0;
		ErrorFlag = true;
	}

	for (int i = 0; i < 32; i++)
	{
		KeepTime[i] = 0;
	}
}

//キー情報をリセットする
void DxJoyPad::ResetKeyData()
{
	KeyState = 0;
	OldKeyState = 0;

	for (int i = 0; i < 32; i++)
	{
		KeepTime[i] = 0;
	}
}

//状態を更新する
void DxJoyPad::UpDate()
{
	if (!ErrorFlag)
	{
		int i;

		//前フレームのキー状態を保持
		OldKeyState = KeyState;

		//現フレームの状態に更新
		KeyState = GetJoypadInputState(InputType);

		//ボタン押下維持状態の更新
		for (i = 0; i < 32; i++)
		{
			if (((KeyState ^ OldKeyState) & (1 << i)) == 0)
			{
				KeepTime[i] ++;
			}
			else
			{
				KeepTime[i] = 0;
			}
		}
	}

}

//指定したキーが押されているかどうか、キー情報と引数をAND演算して返す
//true 押されている false 押されていない
bool DxJoyPad::CheckPress(int keyCode)	const
{
	if ((KeyState & keyCode) == 0)
		return false;
	else
		return true;
}

//前フレームのキー情報と現在のキー情報を比べ、指定したキーが押された瞬間かどうか調べる
//エラーならば、falseを返す true 押された瞬間 false 押された瞬間でない
bool DxJoyPad::CheckPressMoment(int keyCode)	const
{
	if ((KeyState & keyCode) != 0 && (OldKeyState & keyCode) == 0)
		return true;
	else
		return false;
}

//前フレームのキー情報と現在のキー情報を比べ、指定したキーが離された瞬間であるかどうか調べる
//エラーならば、falseを返す true 離された瞬間 false 離された瞬間でない
bool DxJoyPad::CheckFreeMoment(int keyCode)	const
{
	if ((KeyState & keyCode) == 0 && (OldKeyState & keyCode) != 0)
		return true;
	else
		return false;
}

//指定したキーが現在の押下状態を何フレーム維持しているのかを取得する
//押された/離された瞬間なら0
int DxJoyPad::GetTime(int keyNumber)	const
{
	if (keyNumber < 32)
		return KeepTime[keyNumber];
	else
		return 0;	
}

//パッド番号を設定する
//-1 エラー 0 成功
int DxJoyPad::SetInputType(int inputType)
{
	if (inputType <= GetJoypadNum())
	{
		InputType = inputType;
		ErrorFlag = false;
		return 0;
	}

	ErrorFlag = true;
	return -1;
}

//パッド番号を取得する
int DxJoyPad::GetInputType()	const
{
	return InputType;
}

//エラーフラグを取得する
bool DxJoyPad::CheckError()	const
{
	return ErrorFlag;
}