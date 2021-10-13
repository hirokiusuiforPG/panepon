#pragma once
#include"DxControl.h"

class DxKeyBoard : public DxControl
{
protected:
	char KeyState[256];		//キーの押下情報を保持
	char OldKeyState[256];	//前フレームでのキーの押下情報を保持
	int KeepTime[256];		//現在の押下状態を何フレーム維持しているのかを保持

public:
	//コンストラクタ
	DxKeyBoard();

	//キー情報をリセット（全て0）にする
	void ResetKeyData();

	//状態を更新する
	void UpDate();

	//指定したキーが押されているかどうか　キー情報配列の添え字をkeyCodeにしたものを返す
	//エラーならばfalseを返す true押されている false押されていない
	bool CheckPress(int)	const;

	//前フレームのキー情報と現在のキー情報を比べ、指定したキーが押された瞬間かどうかを調べる
	//エラーならば、falseを返す
	bool CheckPressMoment(int)	const;

	//前フレームのキー情報と現在のキー情報を比べ指定したキーが離された瞬間であるかどうかを調べる
	//エラーならば、falseを返す
	bool CheckFreeMoment(int)	const;

	//指定したキーが現在の押下状態を何フレーム維持しているのかを取得する
	//keyCodeが不正ならば、0を返す
	int GetTime(int)	const;
};