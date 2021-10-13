#include "Screen.h"

CScreen::CScreen()
{
	Cursor.Initialize(2, 11);
	//Handle = LoadGraph("dat/img/BG.png");	//”wŒi
}

CScreen::~CScreen()
{
}

void CScreen::Initialize() {
	BlockMgr.Initialize();
	DeleteDecide.Initialize(Cursor.GetThisPtr(), BlockMgr.GetThisPtr());
}

void CScreen::Update() {
	Cursor.Update();
	BlockMgr.Update();
	CrossBlock();
	DeleteDecide.Update();
}

void CScreen::Draw() {
	//DrawGraph(0, 0, Handle, true);//”wŒi
	BlockMgr.Draw();
	Cursor.Draw();//ˆê”ÔŽè‘O
}

void CScreen::Finalize() {

}


void CScreen::CrossBlock()
{
	if (Cursor.CrossSide() == true)
	{
		BlockMgr.SwapBlock(Cursor.GetX(), Cursor.GetY());
	}
}
