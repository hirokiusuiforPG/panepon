#pragma once
#include"DxControl.h"

class DxKeyBoard : public DxControl
{
protected:
	char KeyState[256];		//�L�[�̉�������ێ�
	char OldKeyState[256];	//�O�t���[���ł̃L�[�̉�������ێ�
	int KeepTime[256];		//���݂̉�����Ԃ����t���[���ێ����Ă���̂���ێ�

public:
	//�R���X�g���N�^
	DxKeyBoard();

	//�L�[�������Z�b�g�i�S��0�j�ɂ���
	void ResetKeyData();

	//��Ԃ��X�V����
	void UpDate();

	//�w�肵���L�[��������Ă��邩�ǂ����@�L�[���z��̓Y������keyCode�ɂ������̂�Ԃ�
	//�G���[�Ȃ��false��Ԃ� true������Ă��� false������Ă��Ȃ�
	bool CheckPress(int)	const;

	//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃ��ǂ����𒲂ׂ�
	//�G���[�Ȃ�΁Afalse��Ԃ�
	bool CheckPressMoment(int)	const;

	//�O�t���[���̃L�[���ƌ��݂̃L�[�����׎w�肵���L�[�������ꂽ�u�Ԃł��邩�ǂ����𒲂ׂ�
	//�G���[�Ȃ�΁Afalse��Ԃ�
	bool CheckFreeMoment(int)	const;

	//�w�肵���L�[�����݂̉�����Ԃ����t���[���ێ����Ă���̂����擾����
	//keyCode���s���Ȃ�΁A0��Ԃ�
	int GetTime(int)	const;
};