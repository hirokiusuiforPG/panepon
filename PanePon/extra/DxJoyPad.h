#pragma once
#include"DxControl.h"

class DxJoyPad : public DxControl
{
protected:
	int KeyState;		//キーの押下状態を保持
	int OldKeyState;	//前フレームでのキーの押下状態を保持
	int KeepTime[32];	//現在の押下状態を何フレーム維持しているのかを保持
	int InputType;		//どのパッドから入力を受けるかの識別番号

private:
	bool ErrorFlag;		//エラーが起きたかどうかのフラグ true エラー false 正常

public:
	
	//コンストラクタ
	DxJoyPad();

	//キー情報をリセットする
	void ResetKeyData();

	//状態を更新する
	void UpDate();

	//指定したキーが押されているかどうか、キー情報と引数をAND演算して返す
	//true 押されている false 押されていない
	bool CheckPress(int)	const;

	//前フレームのキー情報と現在のキー情報を比べ、指定したキーが押された瞬間かどうか調べる
	//エラーならば、falseを返す true 押された瞬間 false 押された瞬間でない
	bool CheckPressMoment(int)	const;

	//前フレームのキー情報と現在のキー情報を比べ、指定したキーが離された瞬間であるかどうか調べる
	//エラーならば、falseを返す true 離された瞬間 false 離された瞬間でない
	bool CheckFreeMoment(int)	const;

	//指定したキーが現在の押下状態を何フレーム維持しているのかを取得する
	//押された/離された瞬間なら0
	int GetTime(int)	const;

	//パッド番号を設定する
	//-1 エラー 0 成功
	int SetInputType(int);

	//パッド番号を取得する
	int GetInputType()	const;

	//エラーフラグを取得する
	bool CheckError()	const;
};