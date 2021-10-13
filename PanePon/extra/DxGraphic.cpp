
#include "DxGraphic.h"

/**************************************************************
 *	�O���t�B�b�N��
 **************************************************************
 *	�C���[�W�����擾
 **************************************************************
 *	�����F	
 *	-> �Ȃ�
 *
 *	�߂�l:
 *	int
 *	->	��
 *
 *************************************************************/
int	DxGraphic::GetNumber( void )	const
{
	return HandleArray.size();
}

/**************************************************************
 *	�擾_�O���t�B�b�N�n���h��
 **************************************************************
 *	�擾_�O���t�B�b�N�n���h��
 **************************************************************
 *	�����F	
 *
 *	int number
 *	->	�v�f�ԍ�
 *
 *	�߂�l:
 *	->	int �n���h��
 *	->	�G���[	0
 *
 *************************************************************/
int	DxGraphic::GetHandle( int number )	const
{
	if( number < 0 || ( int ) HandleArray.size() <= number )
		return 0;
	return HandleArray[ number ].Handle;
}

/**************************************************************
 *	����֐�
 **************************************************************
 *	�摜�̉��
 **************************************************************
 *	�����F	
 *	->	�Ȃ�
 *
 *	�߂�l:
 *	->	�Ȃ�
 *
 *************************************************************/
void DxGraphic::Release( void )
{
	// ���
	for( vector< GraphicData >::iterator it = HandleArray.begin(); it != HandleArray.end(); it ++ )
	{
		if( it->BorrowedFlag == 0 )
			DeleteGraph( it->Handle );
	}
	HandleArray.clear();
}

/**************************************************************
 *	�`��֐�
 **************************************************************
 *	�`��
 **************************************************************
 *	�����F	
 *		
 *	XY< int > xy
 *	->	���W
 *
 *	int transFlag
 *	->	���߃t���O
 *	
 *	int number
 *	->	�ԍ�
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int	DxGraphic::Draw( XY< int > xy, int transFlag, int number )
{
	return this->Draw( xy.X, xy.Y, transFlag, number );
}

/**************************************************************
 *	�`��֐�
 **************************************************************
 *	�`��
 **************************************************************
 *	�����F	
 *		
 *	int x, int y
 *	->	���W
 *
 *	int transFlag
 *	->	���߃t���O
 *	
 *	int number
 *	->	�ԍ�
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int	DxGraphic::Draw( int x, int y, int transFlag, int number )
{
	if( number < 0 || ( int ) HandleArray.size() <= number )
		return -1;
	return DrawGraph( x, y, HandleArray[ number ].Handle, transFlag );
}

/**************************************************************
 *	�󂯎��_�O���t�B�b�N�n���h��
 **************************************************************
 *	�؂蕨�t���O�𗧂Ă�
 **************************************************************
 *	�����F	
 *		
 *	const char* filePath
 *	->	�摜�p�X
 *
 *	int numAll, XY< int > num
 *	->	�S�̂̌��ƍ��W�n�ɑ΂��Ă̕�����
 *	
 *	XY< int > size
 *	->	�T�C�Y
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int	DxGraphic::CatchHandle( int handle )
{	
	GraphicData	graphic;
	int			sizeX, sizeY;
	if( handle == -1 )
		return -1;

	if( GetGraphSize( handle, &sizeX, &sizeY ) == -1 )
		return -1;

	graphic.Handle = handle;
	graphic.Size.Set( sizeX, sizeY );

	HandleArray.push_back( graphic );

	return 0;
}

/**************************************************************
 *	�����摜��ǂݍ���
 **************************************************************
 *	�ЂƂ̉摜�𕪊��ǂݍ��݂��A�O���t�B�b�N���X�g�Ƀv�b�V������B
 **************************************************************
 *	�����F	
 *		
 *	const char* filePath
 *	->	�摜�p�X
 *
 *	int numAll, XY< int > num
 *	->	�S�̂̌��ƍ��W�n�ɑ΂��Ă̕�����
 *	
 *	XY< int > size
 *	->	�T�C�Y
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int	DxGraphic::LoadDiv( const char* filePath, int numAll, XY< int > num, XY< int > size )
{
	return this->LoadDiv( filePath, numAll, num.X, num.Y, size.X, size.Y );
}

/**************************************************************
 *	�����摜��ǂݍ���
 **************************************************************
 *	�ЂƂ̉摜�𕪊��ǂݍ��݂��A�O���t�B�b�N���X�g�Ƀv�b�V������B
 **************************************************************
 *	�����F	
 *		
 *	const char* filePath
 *	->	�摜�p�X
 *
 *	int numAll, int numX ,int numY
 *	->	�S�̂̌��ƍ��W�n�ɑ΂��Ă̕�����
 *	
 *	int sizeX, int sizeY
 *	->	�T�C�Y
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int	DxGraphic::LoadDiv( const char* filePath, int numAll, int numX, int numY, int sizeX, int sizeY )
{
	GraphicData	graphic;
	int			*handle;
	
	handle = new int[ numAll ];
	if( handle == NULL )
		return -1;

	// �ǂݍ���
	if( LoadDivGraph( filePath, numAll, numX, numY, sizeX, sizeY, handle ) == -1 )
		return -1;

	for( int i = 0; i < numAll; i ++ )
	{
		int			iSizeX, iSizeY;

		// �T�C�Y�擾
		if( GetGraphSize( handle[ i ], &iSizeX, &iSizeY ) == -1 )
		{
			// ���s
			for( ; i >= 0; i -- )
				DeleteGraph( handle[ i ] );		
			delete[] handle;
			return -1;
		}

		// �ݒ�
		graphic.Handle = handle[ i ];
		graphic.Size.Set( iSizeX, iSizeY );

		// �v�b�V��
		HandleArray.push_back( graphic );
	}

	// ����
	return 0;
}

/**************************************************************
 *	�摜��ǂݍ���
 **************************************************************
 *	�摜��ǂݍ��݁A
 *	���̃O���t�B�b�N�n���h���̏����摜���ێ��\���̂֓���A
 *	�O���t�B�b�N���X�g�Ƀv�b�V������B
 **************************************************************
 *	�����F	
 *		
 *	const char* filePath
 *	->	�摜�p�X
 *
 *	�߂�l:
 *	0	����
 *	-1	���s
 *
 *************************************************************/
int DxGraphic::Load( const char* filePath )
{
	GraphicData	graphic;
	int			handle;
	int			sizeX, sizeY;

	// �ǂݍ���
	handle = LoadGraph( filePath );
	if( handle == -1 )
		return -1;

	// �T�C�Y�擾
	if( GetGraphSize( handle, &sizeX, &sizeY ) == -1 )
	{
		DeleteGraph( handle );
		return -1;
	}

	// �ݒ�
	graphic.Handle = handle;
	graphic.Size.Set( sizeX, sizeY );

	// �v�b�V��
	HandleArray.push_back( graphic );

	// ����
	return 0;
}

/**************************************************************
 *	�R���X�g���N�^
 **************************************************************
 *	�����������s��
 **************************************************************
 *	�����F	
 *		�Ȃ�
 *
 *************************************************************/
DxGraphic::DxGraphic()
{
}

/**************************************************************
 *	�f�X�g���N�^
 **************************************************************
 *	�㏈�����s��
 *	�摜�̉��
 **************************************************************
 *	�����F	
 *		�Ȃ�
 *
 *************************************************************/
DxGraphic::~DxGraphic()
{
	this->Release();
}