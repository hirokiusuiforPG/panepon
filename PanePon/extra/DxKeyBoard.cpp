#pragma once
#include"DxKeyBoard.h"
#include"DxLib.h"

//�R���X�g���N�^
DxKeyBoard::DxKeyBoard()
{
	int i = 0;

	//�ϐ��̏�����
	for (i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
		OldKeyState[i] = 0;
		KeepTime[i] = 0;
	}
}

//�L�[�������Z�b�g�i�S��0�j�ɂ���
void DxKeyBoard::ResetKeyData()
{
	int i;

	//�ϐ��̏�����
	for (i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
		OldKeyState[i] = 0;
		KeepTime[i] = 0;
	}
}

//��Ԃ��X�V����
void DxKeyBoard::UpDate()
{
	int i;

	//���t���[���̏�Ԃ�O�t���[���̏�ԂƂ��ĕێ�����
	for (i = 0; i < 256; i++)
	{
		OldKeyState[i] = KeyState[i];
	}

	//���t���[���̏�Ԃ��X�V
	GetHitKeyStateAll(KeyState);

	//�{�^�������ێ���Ԃ̍X�V
	for (i = 0; i < 256; i++)
	{
		if (KeyState[i] != OldKeyState[i])
		{
			KeepTime[i] = 0;
		}
		else
		{
			KeepTime[i]++;
		}
	}
}

//�w�肵���L�[��������Ă��邩�ǂ����@�L�[���z��̓Y������keyCode�ɂ������̂�Ԃ�
//�G���[�Ȃ��false��Ԃ� true������Ă��� false������Ă��Ȃ�
bool DxKeyBoard::CheckPress(int keyCode)	const
{
	bool ret = false;

	if (keyCode < 256)
	{
		if (KeyState[keyCode] == 1)
		{
			ret = true;
		}
	}

	return ret;
}

//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃ��ǂ����𒲂ׂ�
//�G���[�Ȃ�΁Afalse��Ԃ�
bool DxKeyBoard::CheckPressMoment(int keyCode)	const
{
	if (KeyState[keyCode] - OldKeyState[keyCode] > 0)
		return true;
	else
		return false;
}

//�O�t���[���̃L�[���ƌ��݂̃L�[�����׎w�肵���L�[�������ꂽ�u�Ԃł��邩�ǂ����𒲂ׂ�
//�G���[�Ȃ�΁Afalse��Ԃ�
bool DxKeyBoard::CheckFreeMoment(int keyCode)	const
{
	if (KeyState[keyCode] - OldKeyState[keyCode] < 0)
		return true;
	else
		return false;
}

//�w�肵���L�[�����݂̉�����Ԃ����t���[���ێ����Ă���̂����擾����
//keyCode���s���Ȃ�΁A0��Ԃ�
int DxKeyBoard::GetTime(int keyNumber)	const
{
	if (keyNumber < 256)
	{
		return KeepTime[keyNumber];
	}
	else
	{
		return 0;
	}
}