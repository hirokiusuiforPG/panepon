#pragma once

class DxControl
{
public:
	//�L�[�������Z�b�g�i�S�ĂO�j�ɂ���
	virtual void ResetKeyData() = 0;

	//��Ԃ��X�V����
	virtual void UpDate() = 0;

	//�w�肵���L�[��������Ă��邩�ǂ��� true ������Ă��� false ������Ă��Ȃ�
	virtual bool CheckPress(int keyCode)	const = 0;

	//�w�肵���L�[�������ꂽ�u�Ԃ��ǂ����𒲂ׂ�
	virtual bool CheckPressMoment(int keyCode)	const = 0;

	//�w�肵���L�[�������ꂽ�u�Ԃł��邩�ǂ����𒲂ׂ�
	virtual bool CheckFreeMoment(int keyCode)	const = 0;

	//�w�肵���L�[�����݂̉�����Ԃ����t���[���ێ����Ă���̂����擾����@�����ꂽ/�����ꂽ�u�Ԃ�0
	virtual int GetTime(int keyNumber)	const = 0;
};