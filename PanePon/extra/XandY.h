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

//行列演算（人力）のような処理をする関数類(今後変更するかも)。非常に乱暴な実装である。
namespace MatrixFunctions
{
	//2次元の行列演算を、2次元座標に対して行う。もっぱら回転行列に使う
	template <class T> XY<T> Matrix2D(XY<T> ver, XY<XY<double>> matrix)
	{
		return XY<T>(T(ver.X * matrix.X.X + ver.Y * matrix.X.Y),T(ver.X * matrix.Y.X + ver.Y * matrix.Y.Y));
	}
};

