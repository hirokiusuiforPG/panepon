#include "DxLib.h"
#include "DisposableSound.h"
using namespace std;

/************************************************ 関数の実装 ************************************************/

/************************************************************************************************
関数名：DisposableSound		(コンストラクタ)
引　数：なし
戻り値：なし
機　能：
　変数の初期化を行う。
************************************************************************************************/
DisposableSound::DisposableSound()
{
	PauseFlag = false;
}

/************************************************************************************************
関数名：~DisposableSound		(デストラクタ)
引　数：なし
戻り値：なし
機　能：
　使い捨てサウンドインスタンスが持っている資源を解放する。
************************************************************************************************/
DisposableSound::~DisposableSound()
{
	//すべての資源を解放する
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Release();
		delete (*it);
	}
}

/************************************************************************************************
関数名：AddSound
引　数：なし
戻り値：なし
機　能：
　渡されたサウンドクラスを複製し、再生を開始する。音量もコピーする。
************************************************************************************************/
int DisposableSound::AddSound(const DxSound& original)
{
	//コピー元がサウンドハンドルを保持していないならばエラー終了
	if(original.GetHandle() == -1)return -1;

	//新たにDxSoundクラスを作り、コピー元を複製させる
	DxSound* tempP = new DxSound(original);

	//複製に失敗した場合はdeleteしてエラー終了
	if(tempP->GetHandle() == -1)
	{
		delete tempP;
		return -1;
	}
	//リストにプッシュする
	SoundList.push_back(tempP);
	//ポーズフラグがたっていないならば再生もする。再生形式はバックグラウンド固定
	if(!PauseFlag)
	{
		tempP->Play(DX_PLAYTYPE_BACK,TRUE);
	}
	return 0;
}

/************************************************************************************************
関数名：Check
引　数：なし
戻り値：なし
機　能：
　再生が終了しているサウンドメンバを探す。発見した場合はそれをdeleteし、listから削除する。
************************************************************************************************/
void DisposableSound::Check(void)
{
	//ポーズ中ならそのまま終了
	if(PauseFlag)return ;
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		//再生中でないかをチェックする
		if((*it)->CheckPraying()==0)
		{
			delete (*it);	//デストラクタが作動するので、即deleteでも問題ない
			//リストから削除し、削除後のイテレータを受け取る
			it = SoundList.erase(it);
		}
	}
}

/************************************************************************************************
関数名：Pause
引　数：なし
戻り値：なし
機　能：
　すべてのサウンドの再生を一時停止する。
************************************************************************************************/
void DisposableSound::Pause(void)
{
	//すでにポーズ済みならそのまま終了
	if(PauseFlag)return ;

	//すべてのサウンドを停止する
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Stop();
	}
	PauseFlag = true;
}

/************************************************************************************************
関数名：Reopening
引　数：なし
戻り値：なし
機　能：
　すべてのサウンドの再生を再開する。
************************************************************************************************/
void DisposableSound::Reopening(void)
{
	//すでに再生済みならそのまま終了
	if(!PauseFlag)return ;
	//すべてのサウンドを再生する
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Play(DX_PLAYTYPE_BACK,FALSE);
	}
	PauseFlag = false;
}
