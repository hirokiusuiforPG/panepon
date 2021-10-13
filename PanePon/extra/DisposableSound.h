#pragma once
#include "DxSound.h"
#include <list>

class DisposableSound
{
private:
	DisposableSound(const DisposableSound& another);	//コピーコンストラクタは無効
	std::list<DxSound*> SoundList;		//使い捨てサウンドインスタンスのリスト
	bool				PauseFlag;
public:
	DisposableSound();
	~DisposableSound();
	int		AddSound(const DxSound& original);	//音声を追加（再生）する
	void	Check(void);						//再生が終了しているサウンドメンバを探す。発見した場合はそれをdeleteし、listから削除する。
	void	Pause(void);						//再生を停止する
	void	Reopening(void);					//再生を再開する
	inline	bool	GetPauseFlag(void){return PauseFlag;}
};