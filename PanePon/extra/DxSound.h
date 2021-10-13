#pragma once
#include"DxLib.h"
#include<list>

class DxSound
{
private:
	static	int		MasterVolume;								//このクラスで再生されるすべての音声に対し、それぞれの音量に加えて全体の音量を調節する。
	int				Handle;
	int				Volume;
	static	std::list<DxSound*>	InstanceList;

public:
	DxSound();													//コンストラクタ
	DxSound(const DxSound& original);							//コピーコンストラクタでは「Copy」を実行する
	~DxSound();													//「Release」を実行したあと、インスタンスリストから自身を削除する
	int				Load(const char* filePath);					//指定された音声ファイルを読み込む
	void			Release();									//サウンドハンドルを削除し、変数の初期化を行う。
	int				Play(int PlayType, int TopPositionFlag);	//読み込んだ音声を再生する。
	int				Stop(void);									//再生中の音声を停止する
	int				Copy(const DxSound& original);				//すでに存在するサウンドハンドルを複製する。音量もコピーする。
	bool			CheckPraying(void);							//再生中かをチェックする。
	int				SetLoopPos(int LoopTime);					//ループ再生のためにループ位置を決定する。（ミリ秒単位）
	int				SetLoopSamplePos(int LoopSamplePosition);	//ループ再生のためにループ位置を決定する。（サンプル数単位）

	static	void	SetMasterVolume(int volume);				//マスターボリュームを設定する。
//以下、変数の設定や取得用のinline関数
	//グラフィックハンドル
	inline	int		GetHandle() const {return Handle;}
	//音量
	inline	void	SetVolume(int volume){if((Volume = volume) < 0)Volume = 0;if(Volume > 255)Volume = 255; ChangeVolumeSoundMem( Volume * MasterVolume / 255 , Handle);}
	inline	int		GetVolume() const {return Volume;}
	//マスター音量
	inline	static	int		GetMasterVolume() {return MasterVolume;}

};