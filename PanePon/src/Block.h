#pragma once

#include "DxLib.h"
#include "BaseObject.h"
#include "define.h"
#include <math.h>


enum CAnotherKind
{
	AKnull,			//null
	AKthree,		//1*3
	AKfour,
	AKfive,
	AKsix,			//1*6	
	AKunchain		//1*6	�����ɏ����Ȃ�
};

class CBlock : public CBaseObject
{
	//x,y,GetX,GetY,Init�͂���
	double  x , y;
	int Kind ;
	bool Exist;
	bool Flag;					//DeleteFlag���Ă��ƁB
								//���肷��Ƃ��ɂ����g��Ȃ��ǋL:Delete()�ł��g��
	int Rekind ;
	int Cnt;
	int Counter;

	bool IsOjama;				//Anotherkind�Ŏg���B
	CAnotherKind AnotherKind;

	double UpLiftDrawY;			//1�p�l�������̃p�l��������

	//�o�O�����p BadRepair��
	int CounterFlag;

	//inline void SetPos(double posx, double posy);
	void BadRepair();//
	void IsValid();

public:
	CBlock();
	void Initialize(int posx, int posy, int kind, bool exist, bool flag, int rekind);
	void Update();
	void Draw(int handle);

	inline CBlock *GetThisPtr() { return this; }
	/*
	inline std::vector<CBullet> *GetBulletPtr() { return &Bullet; }

	inline void ApplyDamage(int Damage) { Life -= Damage; ExAnimeFlag = true; }
	*/



	void SetX(double posx) { x = posx; }
	void SetY(double posy) { y = posy; }
	void SetExist(bool exist) { Exist = exist; }
	void SetFlag(bool flag) { Flag = flag; };
	void SetKind(int kind) { Kind = kind; }


	//���ז��p
	void SetIsOjama(bool isojama) { IsOjama = isojama; }
	inline int GetIsOjama() { return IsOjama; }

	inline CAnotherKind GetAnotherKind() { return AnotherKind; }
	inline void SetAnotherKind(CAnotherKind Anotherkind) { AnotherKind = Anotherkind; };



	//���ԍ��̏����p
	void SetCounter(int counter) { Counter = counter; }
	inline int GetCounter() { return Counter; }

	inline int GetKind() { return Kind; }

	inline bool GetExist() { return Exist; }
	inline bool GetFlag() { return Flag; }
	
	inline void UpLiftDraw(double Uy){
			if (Uy > 0)	UpLiftDrawY += Uy;
			else	UpLiftDrawY = 0;
		}
};