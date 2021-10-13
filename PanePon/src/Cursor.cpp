#include "Cursor.h"

CCursor::CCursor() {
	x = 0;
	y = 0;
	Handle = LoadGraph("dat/img/cursorB8.png");
	Angle = 0;
	UpLiftDrawY = 0;
}

void CCursor::Initialize(double posx, double posy){//�^��
	x = posx;
	y = posy;
}

void CCursor::Update() {
	Move();
	//HorChangeXY();
	/*if (CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
	{
		printfDx("%f,%f",x,y);		//���ݒn�\��
	}*/
}

void CCursor::Draw() {//+5 = +300�܂�-300 = 130-300 = -170
	DrawRotaGraphF((float)x * 60 + 180, (float)y * 60 - 170 - UpLiftDrawY, 1.0, 0.0, Handle, true);
}
void CCursor::Move() {
	if (CKey::Inst()->GetKey(KEY_INPUT_RIGHT) == 1)
		x++; 
	if (CKey::Inst()->GetKey(KEY_INPUT_LEFT) == 1)
		x--;
	if (CKey::Inst()->GetKey(KEY_INPUT_UP) == 1)
		y--;
	if (CKey::Inst()->GetKey(KEY_INPUT_DOWN) == 1)
		y++;
	
	if (0 > x)
	{							//���[x
		x = 0;
	}
	if (x > BLOCKSIZE_X - CURSORSIZE_X )		//�E�[x
	{
		x = BLOCKSIZE_X - CURSORSIZE_X;
	}
	if (1 + BlankBlock > y)
	{							//��[y
		y = 1 + BlankBlock;
	}
	if (y > BLOCKSIZE_Y - CURSORSIZE_Y + BlankBlock)		//���[y
	{
		y = BLOCKSIZE_Y - CURSORSIZE_Y + BlankBlock;
	}
}
/*
void CCursor::HorChangeXY() {
	if (CKey::Inst()->GetKey(KEY_INPUT_Z) == 1 )
	{
	}
};
*/

bool CCursor::SwapBlock()		//���E����
{
	if (CKey::Inst()->GetKey(KEY_INPUT_Z) == 1)
	{
		return true;
	}
	return false;
}

