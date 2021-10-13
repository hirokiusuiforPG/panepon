#pragma once
#include "DxGraphic.h"


// �A�j���[�V�����N���X
class DxAnimation
{

private :

	const	DxGraphic*		pGraphicClass;				// ��舵���O���t�B�b�N�N���X�ւ̃|�C���^

	int				NowFrame;					// ���݂̃t���[��
	int				NextStep;					// ���ւ̃X�e�b�v�� 
	int				NowStep;					// ���݂̃X�e�b�v��
	bool			RepeatFlag;					// ���s�[�g�t���O
	GraphicData_PTR	pGraphic;					// �摜�f�[�^�ւ̃|�C���^

public :

	void			Release( void );				// ���
	int				DoStep( int step );				// �X�e�b�v�i�s
	bool			CheckEnd( void )	const;		// �`�F�b�N_�Đ��I��
	
	// ���s�[�g�t���O
	void			SetRepeatFlag( bool repeat );	// �ݒ�
	bool			GetRepeatFlag( void )	const;	// �擾

	void			ToFirst( void );				// �ŏ��֖߂�
	void			ToEnd( void );					// �Ō�܂ōs��

	// �ݒ�_���݂̃t���[��
	int				SetFrameNumber( int frameNumber, bool stepResetFlag );

	// �擾_���݂̃t���[��
	int				GetFrameNumber( void )	const;

	// �ݒ�_���܂ł̃X�e�b�v��
	int				SetNextStep( int stepNumber );

	// �擾_���܂ł̃X�e�b�v��
	int				GetNextStep( void )	const;

	// �O���t�B�b�N�n���h���擾
	int				GetHandle( void )	const;

	// �O���t�B�b�N�N���X�ւ̃|�C���^�̐ݒ�
	void			SetGraphic(	const	DxGraphic* pGraphicClass );

	// �������
	DxAnimation& operator = (const DxAnimation& another);

	// �R���X�g���N�^�A�f�X�g���N�^
	DxAnimation();
	DxAnimation( GraphicData_PTR graphic_ptr );
	DxAnimation( DxGraphic* pGraphicClass );
	//~DxAnimation();

} ;
