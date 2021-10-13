#include "BlockMgr.h"

extern int g_nDifficult;
extern int g_nMode;

CBlockMgr::CBlockMgr()
{
	Handle[0] = LoadGraph("dat/img/Block0.jpg");
	Handle[1] = LoadGraph("dat/img/Block1.jpg");
	Handle[2] = LoadGraph("dat/img/Block2.jpg");
	Handle[3] = LoadGraph("dat/img/Block3.jpg");
	Handle[4] = LoadGraph("dat/img/Block4.jpg");
	Handle[5] = LoadGraph("dat/img/Block5.jpg");
	OjamaHandle[0] = LoadGraph("dat/img/Ojama1.jpg");//3
	OjamaHandle[1] = LoadGraph("dat/img/Ojama2.jpg");//4
	OjamaHandle[2] = LoadGraph("dat/img/Ojama3.jpg");//5
	OjamaHandle[3] = LoadGraph("dat/img/Ojama4.jpg");//6
	OjamaHandle[4] = LoadGraph("dat/img/Ojama5.jpg");//x
	handleB = LoadGraph("dat/img/PanelBoard3.png");

	flag = false;
	HandleClear = LoadGraph("dat/img/clear.png");
	HandleGameOver = LoadGraph("dat/img/GameOver.png");
	HandlePanic = LoadGraph("dat/img/Panic.png");

	//Blockを6*20に
	for (int i = 0; i < 6; i++)
	{
		Block[i].resize(20);//2次元にする
	}

	//***************************************
	//ファイル読み込み
	int n, num, i, fp;
	char fname[32] = { "dat/csv/PanelInit.csv" };	
	int input[64];
	char inputc[64];

	//データ保存用の変数
	double cx, cy;
	int ckind, crekind;
	bool cexist, cflag;

	//とりあえず5こ
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//この中身はInitでやろう。
			Block[i][j].SetX(i);
			Block[i][j].SetY(j);
			Block[i][j].SetFlag(true);		//解釈的には、削除中:false 正常:true
			Block[i][j].SetKind(6);			//空白
			//CreateBlock(i, j, 1, 1, 1, 1);
		}
	}
	
	//パネル配置
	for (int i = 0; i < 6; i++)
	{
		for (int j = 13; j < 18; j++)	//下から２列にブロックを表示
		{
			Block[i][j].SetKind(GetRand(100000) % (g_nDifficult + 2));//色を決める
		}
	}
//	Block[3][12].SetFlag(true);//左３、下３のブロックを存在させる。
	Block[3][12].SetKind(2);
//	Block[1][13].SetFlag(true);//左２、下２のブロックの存在を消す。
	Block[1][13].SetKind(6);	//空白、(flag == false:kind = 6)
	
	BlockInitializer(5,19);		//初期配置


	/*
	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0: cx = atof(inputc); break;
		case 1: cy = atof(inputc); break;
		case 2: ckind = atoi(inputc); break;
		case 3: cexist = atoi(inputc); break;
		case 4: cflag = atoi(inputc); break;
		case 5: crekind = atoi(inputc); break;
		}
		num++;
		if (num == 6) {
			num = 0;
			n++;
			CreateBlock(cx, cy, ckind, cexist, cflag, crekind);	
			//ファイルから参照
		}
	}
EXFILE:
	FileRead_close(fp);
	//***********************************************

	Counter = 0;
	//ゲーム終了関数を作る。update参照
	*/
}

CBlockMgr::~CBlockMgr()
{
}

void CBlockMgr::Initialize() {
}

void CBlockMgr::Finalize() {
}

void CBlockMgr::Update() {
	//Move.Update();
	//Gravity();			//完成したら、Moveに移動

	//Block.Update			//入れるとバグる。
	for (int i = 0; i < 6; i++)
	{
		for (int j = 6; j < 15; j++)
		{
			Block[i][j].Update();//パネルのCounterが勝手に減少するバグを回避する
		}
	}

	CheckPanicFlag();			//パニック状態(GameOverの一歩手前)の判定
}
//難易度修正
void CBlockMgr::Draw() {
							//パネル背景描画
	DrawRotaGraphF(300, 400, 1.0, 0.0, handleB, true);

							//パネル描画
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int k = Block[i][j].GetKind();//ブロックの種類をもってくる
			if (0 <= k && k < 6)				//色ありの場合	
			{
				Block[i][j].Draw(Handle[k]);
			}
			else if (GetAnotherKind(i, j) != AKnull)
			{
				switch (Block[i][j].GetAnotherKind())
				{
				case AKthree:
					Block[i][j].Draw(OjamaHandle[0]);//1*3
					break;
				case AKfour:
					Block[i][j].Draw(OjamaHandle[1]);//1*4
					break;
				case AKfive:
					Block[i][j].Draw(OjamaHandle[2]);//1*5
					break;
				case AKsix:
					Block[i][j].Draw(OjamaHandle[3]);//1*6
					break;
				case AKunchain:
					Block[i][j].Draw(OjamaHandle[4]);//2*6とか
					break;
				default:break;
				}

			}
		}
	}
	Move.Draw();
	switch (DrawFlag)//シーン(0:ゲーム,1:パニック状態,2:GameOver,3:Finish)
	{
	case 0:break;
	case 1:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), HandlePanic, true); break;
	case 2:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), HandleGameOver, true); break;
	case 3:DrawRotaGraph(WINDOWSIZE_X / 2, 100, 1.0, -(PI / 12), Handle[3], true); break;
	default:
		break;
	}
}
///////////////お邪魔用に修正///////////////
void CBlockMgr::Gravity()//色で判断
{
	int keeping = 0;
	int cnt = 0;	//浮いてるのがなくなるまで繰り返す。
	for (int i = 0; i < 6; i++)
	{
		for (int j = 14; j >= 5; j--)			
		{
			if (Block[i][j].GetKind() == 6)	//空白である
			{
				if(keeping == 0)keeping = j;//(お邪魔であっても？)一番下の空白の座標をキープ
				else if (Block[i][j].GetIsOjama() == true) {
					keeping = 0;
				}
				else {}
			}
			else 			//パネルがある
			{
				if (keeping != 0)					//パネルがあって、浮いてる場合
				{
					for (int k = keeping; k > 5; k--)	//一番下の空白の座標を潰す。
					{
						//種類のみ移動
						int temp;
						bool tmp;
						temp = Block[i][k].GetKind();
						Block[i][k].SetKind(Block[i][k - 1].GetKind());	//見えないところ突っ込んでそう
						Block[i][k - 1].SetKind(temp);

						tmp = Block[i][k].GetFlag();
						Block[i][k].SetFlag(Block[i][k - 1].GetFlag());
						Block[i][k - 1].SetFlag(tmp);
						//空白
					}
					cnt++;				//浮いてるのがあったらプラス
					break;				//この列は終わり
				}//浮遊
			}//空白
			
		}//縦列
		keeping = 0;
	}//横列
	if (cnt != 0)	//浮いてるのがあるので繰り返す。
	{
		Gravity();	//もう一回
	}
}
////////////////お邪魔用に修正すべき。///////
//例:Another->kind
void CBlockMgr::SwapBlock(int x,int y)//左右交換
{
	int tmp;
	tmp = Block[x][y].GetKind();//kind -> color
	Block[x][y].SetKind(Block[x + 1][y].GetKind());
	Block[x+1][y].SetKind(tmp);
	tmp = Block[x][y].GetFlag();
	Block[x][y].SetFlag(Block[x + 1][y].GetFlag());
	Block[x + 1][y].SetFlag(tmp);
}

void CBlockMgr::CreateBlock() {		//初期＆パネル生成時の機能
	for (int i = 0; i < 6; i++)	
	{
		Block[i][18].SetKind(GetRand(100000) % (g_nDifficult + 2));
	}
	CheckGameOver();
}

void CBlockMgr::DeleteBlock() {		//不明
	//Blockのクラス->existをFalseにするコード
	//Block->Setexist(False);
}

void CBlockMgr::CheckPanicFlag(){	//パニック状態(GameOver手前)の判定
									//ゲーム範囲外を超えたらgameover
	bool Num = false;
	for (int i = 0; i < 6; i++)
	{
		if (Block[i][6].GetKind() != 6)		//(最上行-1)にパネルがあったら、
		{
			Num = true;//パニック状態
		}
		else if (Block[i][6].GetIsOjama() == true)//お邪魔でも、
		{
			Num = true;//パニック状態
		}
	}
	if (Num  == true)			//パニック状態
	{
		DrawFlag = 1;
	}
	else
	{
		DrawFlag = 0;
	}
}

void CBlockMgr::CheckGameOver()	//DrawFlag (0:普通,1:パニック状態,2:ゲームオーバー,3:Finish)
{
	//パニック状態でパネル生成が行われたらゲームオーバー
	if (DrawFlag == 1)
	{
		DrawFlag = 2;
		flag = true;
	}
}
//難易度修正した。
void CBlockMgr::BlockInitializer(int y1, int y2)	//ブロックが最初から消えないように配置する。
{
	int KindB[7] = { 0 };				//候補となる色 難易度選択から参照したい
	bool CntFlag = true;
	bool Initing = true;
	int Num = 0;

	while (Initing == true && Num < 100)		//100回以上は繰り返さない。
	{
		CntFlag = false;
		Initing = false;
		for (int j = y1; j < y2; j++)		//y2は基本19
		{
			for (int i = 2; i < 6; i++)		//横から走査
			{
				switch (g_nDifficult)
				{
				case 1:			//かんたん
					for (int s = 0; s < 3; s++)		//〇、△、□の候補を1にする。
					{
						KindB[s] = 1;
					}
					break;
				case 2:			//ふつう
					for (int s = 0; s < 4; s++)		//〇、△、□、☆の候補を1にする。
					{
						KindB[s] = 1;
					}
					break;
				case 3:			//難しい
					for (int s = 0; s < 5; s++)		//ハート、〇、△、□、☆の候補を1にする。
					{
						KindB[s] = 1;
					}
					break;
				case 4:			//激ムズ
					for (int s = 0; s < 6; s++)		//ハート、〇、△、□、☆、◇の候補を1にする。
					{
						KindB[s] = 1;
					}
				default:
					break;
				}
				
				if (Block[i][j].GetKind() < 6)		//消えるパネルの時
				{
					if (Block[i - 2][j].GetKind() == Block[i - 1][j].GetKind()		//横の走査
						&& Block[i - 1][j].GetKind() == Block[i][j].GetKind())
					{
						KindB[Block[i][j].GetKind()] = 0;
						CntFlag = true;
					}
					if (j > 1 && y1 < 17)											//縦の走査
					{
						if (Block[i][j - 2].GetKind() == Block[i][j - 1].GetKind()
							&& Block[i][j - 1].GetKind() == Block[i][j].GetKind())
						{
							KindB[Block[i][j].GetKind()] = 0;
							CntFlag = true;
						}
					}
					int k;
					while (CntFlag == true)		//&& Block[i][j].GetKind() < 6
					{
						k = GetRand(100000) % (g_nDifficult + 2);
						if (KindB[k] == 1)
						{
							Block[i][j].SetKind(k);
							CntFlag = false;
							Initing = true;
							break;
						}
					}
				}
			}
		}
		Num++;
	}
	if (y1 < 17)
	{
		//printfDx("\n パネル体裁は%d回続きました。\n", Num);
	}
}

//お邪魔生成	
void CBlockMgr::MakeOjama(int i, int j ,CAnotherKind AnotherKind)//(座標、座標、種類)
{

	//AnotherKindのセット
	Block[i][j].SetAnotherKind(AnotherKind);


	switch (AnotherKind)		//ここの値によって
	{									//横のFlagをtrueにする
	case AKnull:	break;
	case AKthree:
		for (int p = i; p < i + 3; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojamaである
		}
		break;
	case AKfour:
		for (int p = i; p < i + 4; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojamaである
		}
		break;
	case AKfive:
		for (int p = i; p < i + 5; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojamaである
		}
		break;
	case AKsix:
		for (int p = i; p < i + 6; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojamaである
		}
		break;
	case AKunchain:
		for (int p = i; p < i + 6; p++)
		{
			Block[p][j].SetIsOjama(true);	//true : Ojamaである
		}
		break;
	default:
		break;
	}
}
