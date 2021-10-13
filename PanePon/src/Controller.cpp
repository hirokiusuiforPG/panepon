#include "Controller.h"

extern int g_nDifficult;
extern int g_nTimer;
extern int g_nMode;

const char SE1[] = "dat/sound/break.wav";

CController::CController()
{	
	Cursor.Initialize(2, 11);
	Handle1 = LoadGraph("dat/img/PanePon_背景4.jpg");	//背景
	Handle2 = LoadGraph("dat/img/PanePon_背景5.png");	//背景
	Handle3 = LoadGraph("dat/img/PanePon_背景6.jpg");	//隠し
	Handle4 = LoadGraph("dat/img/PanePon_背景7.png");	//隠し

	Timer = 1;			//初回(0)は発動しない
	UpLiftCnt = 1;		//パネル1個分配置するのに使う。
	ComboFlag = false;	//コンボが発生したらtrue
	ComboNum = 0;		//現在のコンボ数
	DeletingFlag = false;	//削除中だったらtrue
	soundflag = 0;

	ScorePoint = 0;
	ScoreCounter = 0;

	for (int i = 0; i < 6; i++)
	{
		Paneltop[i] = 0;
	}

	////GameOver////
	Cr = GetColor(0, 0, 255);        // 青色の値を取得
	GameEnd = 0;
	////////////////
	PauseMode = false;
	X_ButtonMode = false;

	StageTime = 60 * 60 * g_nTimer;
}

CController::~CController()
{
}

void CController::Initialize() {
	BlockMgr.Initialize();
	DeleteDecide.Initialize();
	Rule.Initialize();
	//DeleteDecide.Initialize(Screen.GetThisPtr(), Rule.GetThisPtr());
}

void CController::Update() {
	if (BlockMgr.GetBlockStop() < 2  && !PauseMode )			//ゲームオーバー判定
	{
		if (!X_ButtonMode)
		{
			Cursor.Update();				//カーソル動かす
			BlockMgr.Update();				//中にBlock[][].updateがある

			SwapBlock();					//パネル交換
		}

		BlockMgr.Gravity();				//重力
		Search();						//パネル走査
		Delete();						//削除

		if (!DeletingFlag)				//削除中でない時
		{
			X_button();
			UpLift1();					//せり上げ
		}
		OjamaPush();		//aを押すと出る

		OjamaChange();		//お邪魔->パネル変換
		OjamaPanelTop();
		OjamaGravity();

		Combo();						//連鎖、同時消し
		AddScore();						//ここで音も。
		BlockMgr.Gravity();				//重力
		TimeProcess();
	}

	if(BlockMgr.GetFlag() == true) {
		GameOver();
	}
	else
	{
		Pause();
	}
	Rule.Update();

	DeleteDecide.Update();
}

void CController::Draw() {
	if (g_nMode == 3)
	{
		DrawGraph(0, 0, Handle1, true);
	}
	else if(g_nMode == 2)
	{
		DrawGraph(0, 0, Handle2, true);
	}


	Rule.Draw();
	BlockMgr.Draw();
	Cursor.Draw();//一番手前

/*	if (!BlockMgr.GetFlag() && PauseMode == false)
	{
		if (ComboNum > 0)
		{
			printfDx("%d", ComboNum);
		}
	}*/


	if (BlockMgr.GetFlag())
	{
		DrawBox(500, 400, 850, 540, Cr, TRUE);    // 四角形を描画
		DrawStringToHandle(560, 420, "もう一度", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(560, 470, "やめる", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(500, pointer, "→", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	}
	else if (PauseMode)
	{
		DrawBox(500, 400, 850, 540, Cr, TRUE);    // 四角形を描画
		DrawStringToHandle(560, 420, "続ける", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(560, 470, "やめる", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		DrawStringToHandle(500, pointer, "→", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	}

	//DrawGraph(0, 0, Handle, true);//背景
	
	if (g_nMode == 2)
	{
		if (StageTime <= 0)
		{
			DrawStringToHandle(200, 220, "フィニッシュ！！！", GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
		}
	}

	//DrawStringToHandle(280, 450, "%d", StageTime / 60, GetColor(255, 255, 255), Font01, GetColor(220, 20, 30));
	switch (g_nMode)
	{
	case 1: DrawFormatString(500, 250, GetColor(255, 105, 0), "エンドレス！！");
		break;
	case 2:	DrawFormatString(500, 250, GetColor(255, 0, 0), "残り時間 : %d", StageTime / 60);
		break;
	case 3: DrawFormatString(500, 250, GetColor(255, 105, 0), "おじゃまアタック！");
			DrawFormatString(500, 300, GetColor(255, 0, 0), "残り時間 : %d", StageTime / 60);

			/*DrawFormatString(700, 200, GetColor(120, 55, 155), "お邪魔出現");
			DrawFormatString(700, 250, GetColor(100, 0, 255), "a で 左1 : 1×3のお邪魔");
			DrawFormatString(700, 300, GetColor(100, 0, 255), "s で 左2 : 1×3のお邪魔");
			DrawFormatString(700, 350, GetColor(100, 0, 255), "d で 左3 : 1×3のお邪魔");
			DrawFormatString(700, 400, GetColor(100, 0, 255), "f で 左4 : 1×3のお邪魔");
			DrawFormatString(700, 450, GetColor(100, 0, 255), "g で 1×4のお邪魔");
			DrawFormatString(700, 500, GetColor(100, 0, 255), "h で 1×5のお邪魔");
			DrawFormatString(700, 550, GetColor(100, 0, 255), "j で 1×6のお邪魔");
			DrawFormatString(700, 600, GetColor(100, 0, 255), "k で 2×6のお邪魔");*/
		break;
	default:
			break;
	}
	DrawFormatString(500, 200, GetColor(255, 0, 0), "スコア : %d", ScorePoint);
	DrawBox(50, 705, 600, 710,GetColor(255,0,0),true);

	if (g_nMode == 3)
	{
		DrawGraph(0, 710, Handle3, false);
	}
	else if(g_nMode == 2)
	{
		DrawGraph(0, 710, Handle4, true);
	}

}

void CController::Finalize() {

}
void CController::UpLift1() 
{
	if (X_ButtonMode == false)//押されてない
	{
		//毎秒2.4ピクセル せり上げる	UpLiftRoutine
		if (Timer % (60 / (g_nDifficult + 4)) == 0)			//せり上げ加速時、4倍速 60 -> 15
		{
			UpLiftCnt++;					//少しづつ、せり上げる
			BlockMgr.UpLiftDraw(2.4);		//せり上げ分、追加する
			Cursor.UpLiftDraw(2.4);			//せり上げ分、追加する
		}
		if (UpLiftCnt % 25 == 0)			//25回せり上げたら、
		{
			BlockMgr.CreateBlock();			//ブロック生成
			BlockMgr.BlockInitializer(18, 19);		//18行目のみ
			UpLift2();
			UpLiftCnt = 1;	//＜－理由が分からない。
		}
	}
	else//押されてる時
	{
		if (Timer % 3 == 0)			//せり上げ加速時、4倍速 60 -> 15
		{
			UpLiftCnt++;					//少しづつ、せり上げる
			BlockMgr.UpLiftDraw(2.4);		//せり上げ分、追加する
			Cursor.UpLiftDraw(2.4);			//せり上げ分、追加する
		}
		if (UpLiftCnt % 25 == 0)			//25回せり上げたら、
		{
			BlockMgr.CreateBlock();			//ブロック生成
			BlockMgr.BlockInitializer(18, 19);		//18行目のみ
			UpLift2();
			X_ButtonMode = false;

			UpLiftCnt = 1;	//＜－理由が分からない。
		}
	}
	Timer++;
}

void CController::UpLift2()
{
	//Copy&Paste
	for (int i = 0; i < 6; i++)
	{
		for (int j = 5; j < 20 ; j++)//画面内+せり上げ部分
		{
			//1ブロックずつ上下にkindを交換:自分と上を交換
			int temp ;
			bool tempF;
			CAnotherKind temp1;
			int Ojamatemp;				//SetIsOjama()
			//色のみ
			temp = BlockMgr.GetBlockKind(i, j);							//自分の色を保持
			BlockMgr.SetBlockKind(i,j,BlockMgr.GetBlockKind(i,j-1));	//自分に上のパネルの色
			BlockMgr.SetBlockKind(i, j - 1, temp);						//上のパネルにtempの色

			//Deleteのflag
																		
			//AnotherKind
			temp1 = BlockMgr.GetAnotherKind(i, j);
			BlockMgr.SetAnotherKind(i, j, BlockMgr.GetAnotherKind(i,j-1));
			BlockMgr.SetAnotherKind(i, j - 1, temp1);

			//SetIsOjama
			Ojamatemp = BlockMgr.GetIsOjama(i, j);
			BlockMgr.SetIsOjama(i, j, BlockMgr.GetIsOjama(i, j - 1));
			BlockMgr.SetIsOjama(i, j - 1, Ojamatemp);
		}
	}
	Cursor.UpLiftCursor();			//せり上げの為、1パネル分上に上げる
	Cursor.UpLiftDraw(0);			//1パネル未満の部分	の消去
	BlockMgr.UpLiftDraw(0);			//1パネル未満の部分 の消去
}

void CController::SwapBlock()		//
{
	int x = Cursor.GetX();
	int y = Cursor.GetY();
	if (Cursor.SwapBlock() == true)//カーソルの値を持ってくる。
	{
		if (BlockMgr.GetBlockFlag(x, y) == true && BlockMgr.GetBlockFlag(x + 1, y) == true)//消去中でない
		{
			if (BlockMgr.GetIsOjama(x, y) == false && BlockMgr.GetIsOjama(x+ 1, y) == false)//お邪魔でない
			{
				BlockMgr.SwapBlock(x, y);//左側のブロックを参照	
			}
		}
	}
}

int CController::Search() 
{
	int Cnt = 0;
	int i, j;

	for (i = 0; i < 6; i++)
	{
		int k = 5;
		int Num = 1;
		for (j = 6; j < 15; j++) {

			if (BlockMgr.GetBlockKind(i, k) == BlockMgr.GetBlockKind(i, j))	//連続していたら
			{
				if (BlockMgr.GetBlockKind(i, j) != 6)		//空白でない、連続した色
				{		
					if (BlockMgr.GetBlockCounter(i, j) == 120)//また、削除中でない。
					{
						Num++;
					}
					else//もう既に消えているものだったら、
					{
						Num = 0;		//数えるのをやめる
					}
				}
			}
			else
			{
				if (Num >= 3)			//3個以上の繋がり
				{
					for (; k < j; k++)
					{
						BlockMgr.SetBlockFlagFalse(i, k);
					}
					Cnt++;
				}
				Num = 1;
				k = j;
			}
		}
		if (Num >= 3)			//3個以上の繋がり
		{
			for (; k < j; k++)
			{
				BlockMgr.SetBlockFlagFalse(i, k);
			}
			Cnt++;
		}
	}
	for (j = 5; j < 15; j++)
	{
		int k = 0;
		int Num = 1;
		for (i = 1; i < 6; i++)
		{
			if (BlockMgr.GetBlockKind(k, j) == BlockMgr.GetBlockKind(i, j))
			{			
				if (BlockMgr.GetBlockKind(i, j) != 6)		//空白でない、連続した色
				{
					if(BlockMgr.GetBlockCounter(i,j) == 120)//削除中でない時
					{
						Num++;
					}
					else//もう既に消えているものだったら、
					{
						Num = 0;		//数えるのをやめる
					}

				}
			}
			else
			{
				if (Num >= 3)			//3個以上の繋がり
				{
					for (; k < i; k++)
					{
						BlockMgr.SetBlockFlagFalse(k, j);
					}
					Cnt++;
				}
				Num = 1;
				k = i;
			}
		}
		if (Num >= 3)			//3個以上の繋がり
		{
			for (; k < i; k++)
			{
				BlockMgr.SetBlockFlagFalse(k, j);
			}
			Cnt++;
		}
	}
	return Cnt;
}

void CController::Delete()
{
	int i, j;

	for (i = 0; i <6; i++)
	{
		for (j = 5; j < 15; j++)
		{
			if (BlockMgr.GetBlockFlag(i, j) == false)	//削除判定ON
			{
				if (BlockMgr.GetBlockCounter(i, j) <= 0)	//時間差で消す。
				{
					BlockMgr.SetBlockKind(i, j, 6);		//6 = 空白
					BlockMgr.SetBlockFlagTrue(i, j);	//削除終わった
					BlockMgr.SetBlockCounter(i, j, 120);	//カウンターを120にする。
					ComboFlag = true;					//combo()で使用
					ScoreCounter++;
					soundflag = 1;
				}
				else {	//削除判定は出たパネルのカウンターを減らす。
					//カウンターをマイナスする。
					BlockMgr.ReduceBlockCounter(i, j);
				}
				//Delete.all  = true //削除判定がなくなるまで、comboをリセットしない
				DeletingFlag = true;
			}
		}
	}
}

void CController::Combo()
{
	if (soundflag == 1)
	{
		PlaySoundFile("dat/sound/break.wav", DX_PLAYTYPE_BACK);
	}
	if (ComboFlag == true)
	{
		ComboNum++;
	}
	else if (DeletingFlag == false)
	{
			ComboNum = 0;		//コンボ
	}
	ComboFlag = false;
	DeletingFlag = false;
	soundflag = 0;
}

void CController::AddScore() {
	if (ScoreCounter > 1)
	{
		//スコアカウント
		ScorePoint = ScorePoint + (ScoreCounter + 100) * ComboNum * ScoreCounter;
		ScoreCounter = 0;
	}

}

void CController::GameOver()
{
	if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
	{
		switch (pointer)
		{
		case 420: GameEnd = 1; break;
		case 470: GameEnd = 2; break;//シーンを終了する
		}
	}

	if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1) {		//矢印を上に。
		if (pointer != 420) {
			pointer -= 50;
		}
		else {
			pointer = 470;
		}
	}
	if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1) {	//矢印を上に。
		if (pointer != 470) {
			pointer += 50;
		}
		else {
			pointer = 420;
		}
	}


}

void CController::Pause()
{
	if (!BlockMgr.GetFlag())		//ゲームオーバーでない時
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_Q) == 1)
		{
			if (!PauseMode)
			{
				PauseMode = true;
			}
			else
			{
				PauseMode = false;
			}
		}
	}
	if (PauseMode == true)
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_RETURN) == 1 || CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
		{
			switch (pointer)
			{
			case 420: PauseMode = false; break;
			case 470: GameEnd = 2; break;//シーンを終了する
			}
		}

		if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1)
		{		//矢印を上に。
			if (pointer != 420) {
				pointer -= 50;
			}
			else {
				pointer = 470;
			}
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1)
		{	//矢印を上に。
			if (pointer != 470) {
				pointer += 50;
			}
			else
			{
				pointer = 420;
			}
		}
	}
}

void CController::TimeProcess()
{
	if (g_nMode == 2 || g_nMode == 3)				//スコアアタックモードだったら
	{
		if (StageTime > 0)			//時間制限あり
			StageTime--;
		if (StageTime == 0)
		{
			BlockMgr.SetGameFinishFlag();//パネルにゲーム終了を伝える
		}
	}
}

void CController::X_button()
{
	if (!BlockMgr.GetFlag())		//ゲームオーバーでない時
	{
		if (CKey::Inst()->GetKey(KEY_INPUT_X) > 1)	//xを押されている
		{
			X_ButtonMode = true;
		}
	}
}

void CController::OjamaGravity()	//空白はここで全部落ちる
{
	//お邪魔を見つける。
	//お邪魔のAnotherKindの値によって、参照するtopの値を変える。
	//topの-1にAnotherKindを移動する。
	//Getした部分の
	//topを更新する
	//続きからお邪魔を調べる。
	
	int Maxtop = 0;		//列の最大の高さを得る
	

	for (int j = 15; j >= 0; j--)	//縦
	{
		//下から見ていく
		for (int i = 0; i < 6; i++)	//横
		{
			if (BlockMgr.GetAnotherKind(i, j) != AKnull)	//お邪魔だった
			{
				switch (BlockMgr.GetAnotherKind(i, j))			//AnotherKind見る
				{
				case AKnull:	//何もしない
					break;
				case AKthree:
					Maxtop = 20;			//パネルの頂点を保持
					for (int p = i; p < i + 3; p++)		//横３つ調べる
					{
						if (Maxtop > Paneltop[p])		//小さい時
						{
							Maxtop = Paneltop[p];		//Maxtopを更新
						}//top最大値を取得
					}
					//AnotherKindをtop-1に更新
					if (j != Maxtop - 1)		//位置が変わる時
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKthree);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//元の位置を更新

						for (int p = i; p < i + 3; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//更新
							BlockMgr.SetIsOjama(p, j, false);			//元を消す。
						}
					}
					//paneltopを更新
					for (int p = i; p < i + 3; p++)//その列の部分の
					{
						Paneltop[p] = Maxtop - 1;		//topの更新
					}
					break;
				case AKfour:	
					Maxtop = 20;			//初期化
					for (int p = i; p < i + 4; p++)		//横4つ調べる
					{
						if (Maxtop > Paneltop[p])		//小さい時
						{
							Maxtop = Paneltop[p];		//Maxtopを更新
						}//top最大値を取得
					}
					//AnotherKindをtop-1に更新
					if (j != Maxtop - 1)		//値が動いたときのみ
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKfour);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//元の位置を更新

						for (int p = i; p < i + 4; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//更新
							BlockMgr.SetIsOjama(p, j, false);			//元を消す。
						}
					}
													//paneltopを更新
					for (int p = i; p < i + 4; p++)	//その列の部分の
					{
						Paneltop[p] = Maxtop - 1;		//topの更新
					}
					break;
				case AKfive:	
					Maxtop = 20;			//初期化
					for (int p = i; p < i + 5; p++)		//横5つ調べる
					{
						if (Maxtop > Paneltop[p])		//小さい時
						{
							Maxtop = Paneltop[p];		//Maxtopを更新
						}//top最大値を取得
					}
					//AnotherKindをtop-1に更新
					if (j != Maxtop - 1)		//値が動いたときのみ
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKfive);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//元の位置を更新

						for (int p = i; p < i + 5; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//更新
							BlockMgr.SetIsOjama(p, j, false);			//元を消す。
						}
					}
																//paneltopを更新
					for (int p = i; p < i + 5; p++)//その列の部分の
					{
						Paneltop[p] = Maxtop - 1;		//topの更新
					}
					break;
				case AKsix:		
					Maxtop = 20;			//初期化
					for (int p = i; p < i + 6; p++)		//横３つ調べる
					{
						if (Maxtop > Paneltop[p])		//小さい時
						{
							Maxtop = Paneltop[p];		//Maxtopを更新
						}//top最大値を取得
					}
					//AnotherKindをtop-1に更新
					if (j != Maxtop - 1)		//値が動いたときのみ
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKsix);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//元の位置を更新

						for (int p = i; p < i + 6; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//更新
							BlockMgr.SetIsOjama(p, j, false);			//元を消す。
						}
					}
																//paneltopを更新
					for (int p = i; p < i + 6; p++)//その列の部分の
					{
						Paneltop[p] = Maxtop - 1;		//topの更新
					}
					break;
				case AKunchain:
					Maxtop = 20;			//初期化
					for (int p = i; p < i + 6; p++)		//横３つ調べる
					{
						if (Maxtop > Paneltop[p])		//小さい時
						{
							Maxtop = Paneltop[p];		//Maxtopを更新
						}//top最大値を取得
					}
					//AnotherKindをtop-1に更新
					if (j != Maxtop - 1)		//値が動いたときのみ
					{
						BlockMgr.SetAnotherKind(i, Maxtop - 1, AKunchain);
						BlockMgr.SetAnotherKind(i, j, AKnull);		//元の位置を更新

						for (int p = i; p < i + 6; p++)
						{
							BlockMgr.SetIsOjama(p, Maxtop - 1, true);	//更新
							BlockMgr.SetIsOjama(p, j, false);			//元を消す。
						}
					}
																//paneltopを更新
					for (int p = i; p < i + 6; p++)//その列の部分の
					{
						Paneltop[p] = Maxtop - 1;		//topの更新
					}
					break;
				default:
					break;
				}
			}//頂点を取った。
		}
	}
	//全データを下げる(例外処理)
}

void CController::OjamaPanelTop()
{
	int top = 20;
	for (int i = 0; i < 6; i++)				//各列に
	{
		for (int j = 14; j >= 5; j--)		//下から走査
		{
			if (BlockMgr.GetBlockKind(i, j) < 6)		//パネルの時
			{
				top = j;			//座標取得
			}
		}
		Paneltop[i] = top;			//座標最大値を列ごとに保持
	}
}

void CController::OjamaChange()//パネル変換
{
	bool Flag1 = false;		
	bool Flag2 = false;
	bool Flag3 = false;//three
	bool Flag4 = false;//three

	for (int j = 14; j >= 5; j--)//下から
	{

		for (int i = 0; i < 4; i++)//横に調べる
		{
			if (BlockMgr.GetAnotherKind(i, j) != AKnull)		//お邪魔存在する時
			{
				switch (BlockMgr.GetAnotherKind(i, j))			//AnotherKind見る
				{
				case AKnull:	break;
				case AKthree:

					for (int p = i; p < i + 3; p++)		//3つのブロックの
					{//上下左右を見る。

						if (Flag3 == true && p >= 4) {//pが飛び抜けないように
						}
						else if (Flag4 == true && p <= 0) {
						}
						else if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //上	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);			//Ojamaを消す
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//下	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKthree, false);
						}
						else if (i >= 1)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//左	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKthree, false);
							}
						}
						else if (i <= 5)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//右	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKthree, false);
							}
						}

					}
					if (i == 0 && Flag1 == true) {
						Flag3 = true;
					}
					if (i == 4 && Flag1 == true) {
						Flag4 = true;
					}

					break;
				case AKfour:
					for (int p = i; p < i + 4; p++)		//4つのブロックの
					{//上下左右を見る。

						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //上	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);			//Ojamaを消す
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//下	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfour, false);
						}
						else if (i >= 1)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//左	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfour, false);
							}
						}
						else if (i <= 5)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//右	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfour, false);
							}
						}
					}
					break;
				case AKfive:
					for (int p = i; p < i + 5; p++)		//3つのブロックの
					{//上下左右を見る。
						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);
							Flag2 = false;
						}
						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //上	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);			//Ojamaを消す
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//下	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKfive, false);
						}
						else if (i >= 1)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//左	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfive, false);
							}
						}
						else if (i <= 5)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//右	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKfive, false);
							}
						}

					}
					break;
				case AKsix:
					for (int p = i; p < i + 6; p++)		//3つのブロックの
					{//上下左右を見る。
						if (Flag1 == true)
						{
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);
							Flag2 = false;
						}
						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //上	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);			//Ojamaを消す
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//下	隣接して消した
						{
							Flag1 = true;
							OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKnull);
							SetOjama(i, j, AKsix, false);
						}
						else if (i >= 1)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//左	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKsix, false);
							}
						}
						else if (i <= 5)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//右	隣接して消した
							{
								Flag1 = true;
								OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKnull);
								SetOjama(i, j, AKsix, false);
							}
						}
					}
					break;
				case AKunchain:
					for (int p = i; p < i + 6; p++)		//3つのブロックの
					{//上下左右を見る。
						if (Flag1 == true)
						{
							//OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);
							Flag2 = false;
						}

						else if (BlockMgr.GetBlockFlag(p, j - 1) == false) //上	隣接して消した
						{
							Flag1 = true;
						//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);			//Ojamaを消す
						}
						else if (BlockMgr.GetBlockFlag(p, j + 1) == false)	//下	隣接して消した
						{
							Flag1 = true;
							//OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
							BlockMgr.SetAnotherKind(i, j, AKsix);
							SetOjama(i, j, AKsix, true);
						}
						else if (i >= 1)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p - 1, j) == false)	//左	隣接して消した
							{
								Flag1 = true;
							//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKsix);
								SetOjama(i, j, AKsix, true);
							}
						}
						else if (i <= 5)		//範囲外処理
						{
							if (BlockMgr.GetBlockFlag(p + 1, j) == false)	//右	隣接して消した
							{
								Flag1 = true;
							//	OjamaMakePanel(i, j, BlockMgr.GetAnotherKind(i, j));	//パネルに変換
								BlockMgr.SetAnotherKind(i, j, AKsix);
								SetOjama(i, j, AKsix, true);
							}
						}

					}
					break;
				default:
						break;
				}
			}
		}
		if (Flag1 == true)
		{
			if (Flag2 == true)
			{
				Flag1 = false;
				Flag2 = false;
				Flag3 = false;
				Flag4 = false;
			}
			else
			{
				Flag2 = true;
			}
		}
	}
}

void CController::OjamaMakePanel(int i, int j, CAnotherKind Anotherkind)
{
	switch (Anotherkind)
	{
	case AKnull:	break;
	case AKthree:
		for (int p = i; p < i + 3; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//ブロックを生成
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//ブロックを生成
		}
		break;
	case AKfive:	
		for (int p = i; p < i + 5; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//ブロックを生成
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//ブロックを生成
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)
		{
			BlockMgr.SetBlockKind(p, j, GetRand(100000) % (g_nDifficult + 2));	//ブロックを生成
		}
		break;
	}
	
	BlockMgr.BlockInitializer(j, j + 1);		//消えないように配置
}

//お邪魔を手動で生成
void CController::OjamaPush()		
{
	int tmp = 0;
	switch (g_nDifficult)
	{
	case 1:tmp = GetRand(3000); break;
	case 2:tmp = GetRand(2000); break;
	case 3:tmp = GetRand(1500); break;
	case 4:tmp = GetRand(1000); break;
	}
	if (g_nMode == 3)
	{
		switch (tmp)
		{
		case 1:BlockMgr.MakeOjama(0, 0, AKthree); break;
		case 2:BlockMgr.MakeOjama(2, 0, AKthree); break;
		case 3:BlockMgr.MakeOjama(3, 0, AKthree); break;
		case 4:BlockMgr.MakeOjama(0, 0, AKfour); break;
		case 5:BlockMgr.MakeOjama(0, 0, AKfive); break;
	//	case 5:BlockMgr.MakeOjama(0, 0, AKunchain);
	//		BlockMgr.MakeOjama(0, 1, AKsix);
			break;
		default:break;
		}
		/*
		//デバック用
		if (CKey::Inst()->GetKey(KEY_INPUT_A) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_S) == 1)
		{
			BlockMgr.MakeOjama(1, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_D) == 1)
		{
			BlockMgr.MakeOjama(2, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_F) == 1)
		{
			BlockMgr.MakeOjama(3, 0, AKthree);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_G) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKfour);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_H) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKfive);
		}
		if (CKey::Inst()->GetKey(KEY_INPUT_J) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKsix);
		}
		
		if (CKey::Inst()->GetKey(KEY_INPUT_K) == 1)
		{
			BlockMgr.MakeOjama(0, 0, AKunchain);
			BlockMgr.MakeOjama(0, 1, AKsix);
		}
		*/
	}
}

//お邪魔フラグをセットする。
void CController::SetOjama(int i, int j, CAnotherKind AnotherKind, bool flag)
{
	switch (AnotherKind)		//AnotherKindの値によって、
	{
	case AKnull:break;
	case AKthree:
		for (int p = i; p < i + 3; p++)		//3つのブロックのフラグをfalseにする。
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//フラグをfalseにする
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//フラグをtrueにする
			}
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)		//3つのブロックのフラグをfalseにする。
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//フラグをfalseにする
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//フラグをtrueにする
			}
		}
		break;
	case AKfive:
		for (int p = i; p < i + 5; p++)		//3つのブロックのフラグをfalseにする。
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//フラグをfalseにする
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//フラグをtrueにする
			}
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)		//3つのブロックのフラグをfalseにする。
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//フラグをfalseにする
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//フラグをtrueにする
			}
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)		//3つのブロックのフラグをfalseにする。
		{
			if (flag == false)
			{
				BlockMgr.SetIsOjama(p, j, false);	//フラグをfalseにする
			}
			else
			{
				BlockMgr.SetIsOjama(p, j, true);	//フラグをtrueにする
			}
		}
		break;

	default:
		break;
	}
}
