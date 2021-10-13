#pragma once
#include "DxSound.h"
#include <list>

class DisposableSound
{
private:
	DisposableSound(const DisposableSound& another);	//�R�s�[�R���X�g���N�^�͖���
	std::list<DxSound*> SoundList;		//�g���̂ăT�E���h�C���X�^���X�̃��X�g
	bool				PauseFlag;
public:
	DisposableSound();
	~DisposableSound();
	int		AddSound(const DxSound& original);	//������ǉ��i�Đ��j����
	void	Check(void);						//�Đ����I�����Ă���T�E���h�����o��T���B���������ꍇ�͂����delete���Alist����폜����B
	void	Pause(void);						//�Đ����~����
	void	Reopening(void);					//�Đ����ĊJ����
	inline	bool	GetPauseFlag(void){return PauseFlag;}
};