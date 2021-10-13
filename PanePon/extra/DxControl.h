#pragma once

class DxControl
{
public:
	//キー情報をリセット（全て０）にする
	virtual void ResetKeyData() = 0;

	//状態を更新する
	virtual void UpDate() = 0;

	//指定したキーが押されているかどうか true 押されている false 押されていない
	virtual bool CheckPress(int keyCode)	const = 0;

	//指定したキーが押された瞬間かどうかを調べる
	virtual bool CheckPressMoment(int keyCode)	const = 0;

	//指定したキーが離された瞬間であるかどうかを調べる
	virtual bool CheckFreeMoment(int keyCode)	const = 0;

	//指定したキーが現在の押下状態を何フレーム維持しているのかを取得する　押された/離された瞬間は0
	virtual int GetTime(int keyNumber)	const = 0;
};