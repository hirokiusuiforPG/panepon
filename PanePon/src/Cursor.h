#pragma once

#include "DxLib.h"
#include "BaseObject.h"
#include "key.h"
#include "define.h"
#include "BlockMgr.h"
#include "Move.h"


class CCursor : public CBaseObject
{
	int Handle;		//画像ハンドル
	double Angle;	//角度

	double UpLiftDrawY;		//絶対値

	//std::list<CBullet> Bullet;	//弾の配列
	//std::list<CAniki> Aniki;	//兄貴の配列
	bool Flag;		

	void Move();		//移動
	//void HorChangeXY();	//左右交換

public:
	CCursor();

	void Initialize(double posx, double posy);
	void Update();
	void Draw();

	bool SwapBlock();

	//判定用
	inline CCursor *GetThisPtr() { return this; }
	inline void UpLiftCursor() { y--; }
	inline void UpLiftDraw(double Uy) { 
		if(Uy > 0)	UpLiftDrawY += Uy;
		else	UpLiftDrawY = 0;
	}
	/*
	inline std::list<CBullet> *GetBulletPtr() { return &Bullet; }
	inline int GetDamage() { return 1; }

	void ApplyDamage(int Damage);
	*/
};