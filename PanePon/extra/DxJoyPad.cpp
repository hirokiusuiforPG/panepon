#pragma once
#include"DxJoyPad.h"
#include"DxLib.h"

//�R���X�g���N�^
DxJoyPad::DxJoyPad()
{
	KeyState = 0;
	OldKeyState = 0;

	//�W���C�p�b�h�̐ڑ����m�F���A���͂�ݒ肷��
	if (GetJoypadNum() > 0)
	{
		InputType = DX_INPUT_PAD1;
		ErrorFlag = false;
	}
	else
	{
		InputType = 0;
		ErrorFlag = true;
	}

	for (int i = 0; i < 32; i++)
	{
		KeepTime[i] = 0;
	}
}

//�L�[�������Z�b�g����
void DxJoyPad::ResetKeyData()
{
	KeyState = 0;
	OldKeyState = 0;

	for (int i = 0; i < 32; i++)
	{
		KeepTime[i] = 0;
	}
}

//��Ԃ��X�V����
void DxJoyPad::UpDate()
{
	if (!ErrorFlag)
	{
		int i;

		//�O�t���[���̃L�[��Ԃ�ێ�
		OldKeyState = KeyState;

		//���t���[���̏�ԂɍX�V
		KeyState = GetJoypadInputState(InputType);

		//�{�^�������ێ���Ԃ̍X�V
		for (i = 0; i < 32; i++)
		{
			if (((KeyState ^ OldKeyState) & (1 << i)) == 0)
			{
				KeepTime[i] ++;
			}
			else
			{
				KeepTime[i] = 0;
			}
		}
	}

}

//�w�肵���L�[��������Ă��邩�ǂ����A�L�[���ƈ�����AND���Z���ĕԂ�
//true ������Ă��� false ������Ă��Ȃ�
bool DxJoyPad::CheckPress(int keyCode)	const
{
	if ((KeyState & keyCode) == 0)
		return false;
	else
		return true;
}

//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃ��ǂ������ׂ�
//�G���[�Ȃ�΁Afalse��Ԃ� true �����ꂽ�u�� false �����ꂽ�u�ԂłȂ�
bool DxJoyPad::CheckPressMoment(int keyCode)	const
{
	if ((KeyState & keyCode) != 0 && (OldKeyState & keyCode) == 0)
		return true;
	else
		return false;
}

//�O�t���[���̃L�[���ƌ��݂̃L�[�����ׁA�w�肵���L�[�������ꂽ�u�Ԃł��邩�ǂ������ׂ�
//�G���[�Ȃ�΁Afalse��Ԃ� true �����ꂽ�u�� false �����ꂽ�u�ԂłȂ�
bool DxJoyPad::CheckFreeMoment(int keyCode)	const
{
	if ((KeyState & keyCode) == 0 && (OldKeyState & keyCode) != 0)
		return true;
	else
		return false;
}

//�w�肵���L�[�����݂̉�����Ԃ����t���[���ێ����Ă���̂����擾����
//�����ꂽ/�����ꂽ�u�ԂȂ�0
int DxJoyPad::GetTime(int keyNumber)	const
{
	if (keyNumber < 32)
		return KeepTime[keyNumber];
	else
		return 0;	
}

//�p�b�h�ԍ���ݒ肷��
//-1 �G���[ 0 ����
int DxJoyPad::SetInputType(int inputType)
{
	if (inputType <= GetJoypadNum())
	{
		InputType = inputType;
		ErrorFlag = false;
		return 0;
	}

	ErrorFlag = true;
	return -1;
}

//�p�b�h�ԍ����擾����
int DxJoyPad::GetInputType()	const
{
	return InputType;
}

//�G���[�t���O���擾����
bool DxJoyPad::CheckError()	const
{
	return ErrorFlag;
}