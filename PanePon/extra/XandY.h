#pragma once
#include <cmath>
template <class tXY> class XY
{
public:
	tXY X,Y;
	inline			XY(){}
	inline			XY(tXY x,tXY y){this->X=x;this->Y=y;};
	inline	XY<tXY>	Set(tXY x, tXY y){ this->X = x; this->Y = y; return *this; };
	inline	XY<tXY>	Scale(double scale){return XY<tXY>(tXY(this->X*scale),tXY(this->Y*scale));}
	inline	double	Size(void){return sqrt(double(this->X*this->X+this->Y*his->Y));}
	inline	double	Distance(XY<tXY>& another){return sqrt(double((another.X - this->X)*(another.X - this->X)+(another.Y - this->Y)*(another.Y - this->Y)));}
	inline	bool	operator==(XY<tXY>& another){return (this->X == another.X && this->Y == another.Y);}
	inline	bool	operator!=(XY<tXY>& another){return (this->X != another.X || this->Y != another.Y);}
	inline	XY&		operator=(XY<tXY>& another){this->X = another.X; this->Y = another.Y; return *this;}
	inline	XY&		operator+=(XY<tXY>& another){this->X += another.X; this->Y += another.Y; return *this;}
	inline	XY&		operator-=(XY<tXY>& another){this->X -= another.X; this->Y -= another.Y; return *this;}
	inline	XY		operator+(XY<tXY>& another){return XY<tXY>(this->X + another.X , this->Y + another.Y);}
	inline	XY		operator-(XY<tXY>& another){return XY<tXY>(this->X - another.X , this->Y - another.Y);}
};

//�s�񉉎Z�i�l�́j�̂悤�ȏ���������֐���(����ύX���邩��)�B���ɗ��\�Ȏ����ł���B
namespace MatrixFunctions
{
	//2�����̍s�񉉎Z���A2�������W�ɑ΂��čs���B�����ς��]�s��Ɏg��
	template <class T> XY<T> Matrix2D(XY<T> ver, XY<XY<double>> matrix)
	{
		return XY<T>(T(ver.X * matrix.X.X + ver.Y * matrix.X.Y),T(ver.X * matrix.Y.X + ver.Y * matrix.Y.Y));
	}
};

