#pragma once

#include "DxLib.h"
#include "BaseObject.h"
#include "key.h"
#include "define.h"
#include "BlockMgr.h"
#include "Move.h"


class CCursor : public CBaseObject
{
	int Handle;		//�摜�n���h��
	double Angle;	//�p�x

	double UpLiftDrawY;		//��Βl

	//std::list<CBullet> Bullet;	//�e�̔z��
	//std::list<CAniki> Aniki;	//�Z�M�̔z��
	bool Flag;		

	void Move();		//�ړ�
	//void HorChangeXY();	//���E����

public:
	CCursor();

	void Initialize(double posx, double posy);
	void Update();
	void Draw();

	bool SwapBlock();

	//����p
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