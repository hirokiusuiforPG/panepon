#pragma once

typedef enum {
	eScene_Genre,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Config,  //設定画面
	eScene_Exit,
	eScene_None,    //無し
	eScene_Start,
	eScene_Achievement,
} eScene ;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};