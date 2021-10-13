#pragma once
#include"DxControl.h"

class DxJoyPad : public DxControl
{
protected:
	int KeyState;		//�L�[�̉�����Ԃ�ێ�
	int OldKeyState;	//�O�t���[���ł̃L�[�̉�����Ԃ�ێ�
	int KeepTime[32];	//���݂̉�����Ԃ����t���[���ێ����Ă���̂���ێ�
	int InputType;		//�ǂ̃p�b�h������͂��󂯂邩�̎��ʔԍ�

private:
	bool ErrorFlag;		//�G���[���N�������ǂ����̃t���O true �G���[ false ����

public:
	
	//�R���X�g���N�^
	DxJoyPad();

	//�L�[�������Z�b�g����
	void ResetKeyData();

	//��Ԃ��X�V����
	void UpDate();

	//�w�肵���L�[��������Ă��邩�ǂ����A�L�[���ƈ�����AND���Z���ĕԂ�
	//true ������Ă��� false ������Ă��Ȃ�
	bool CheckPress(int)	const;

	//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃ��ǂ������ׂ�
	//�G���[�Ȃ�΁Afalse��Ԃ� true �����ꂽ�u�� false �����ꂽ�u�ԂłȂ�
	bool CheckPressMoment(int)	const;

	//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃł��邩�ǂ������ׂ�
	//�G���[�Ȃ�΁Afalse��Ԃ� true �����ꂽ�u�� false �����ꂽ�u�ԂłȂ�
	bool CheckFreeMoment(int)	const;

	//�w�肵���L�[�����݂̉�����Ԃ����t���[���ێ����Ă���̂����擾����
	//�����ꂽ/�����ꂽ�u�ԂȂ�0
	int GetTime(int)	const;

	//�p�b�h�ԍ���ݒ肷��
	//-1 �G���[ 0 ����
	int SetInputType(int);

	//�p�b�h�ԍ����擾����
	int GetInputType()	const;

	//�G���[�t���O���擾����
	bool CheckError()	const;
};