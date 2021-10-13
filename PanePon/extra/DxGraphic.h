#pragma once
#include "DxLib.h"
#include "GraphicData.h"

#include <vector>
using namespace std;


// �O���t�B�b�N�N���X
class DxGraphic
{

private :

	vector< GraphicData >	HandleArray;			// �O���t�B�b�N���X�g

public :

	// �摜��ǂݍ���
	int					Load( const char* filePath );

	// �����ǂݍ���
	int					LoadDiv( const char* filePath, int numAll, int numX, int numY, int sizeX, int sizeY );
	int					LoadDiv( const char* filePath, int numAll, XY< int > num, XY< int > size );
	
	// �󂯎��_�O���t�B�b�N�n���h��
	int					CatchHandle( int handle );

	// �`��
	int					Draw( int x, int y, int transFlag, int number = 0 );
	int					Draw( XY< int > xy, int transFlag, int number = 0 );

	// �摜�̉��
	void				Release( void );

	// �擾_�O���t�B�b�N�n���h��
	int					GetHandle( int number = 0 )	const;

	// �擾_�摜��
	int					GetNumber( void )	const;
		
	// �R���X�g���N�^�A�f�X�g���N�^
	DxGraphic();
	~DxGraphic();

} ;