#pragma once
#include"DxLib.h"
#include<list>

class DxSound
{
private:
	static	int		MasterVolume;								//���̃N���X�ōĐ�����邷�ׂẲ����ɑ΂��A���ꂼ��̉��ʂɉ����đS�̂̉��ʂ𒲐߂���B
	int				Handle;
	int				Volume;
	static	std::list<DxSound*>	InstanceList;

public:
	DxSound();													//�R���X�g���N�^
	DxSound(const DxSound& original);							//�R�s�[�R���X�g���N�^�ł́uCopy�v�����s����
	~DxSound();													//�uRelease�v�����s�������ƁA�C���X�^���X���X�g���玩�g���폜����
	int				Load(const char* filePath);					//�w�肳�ꂽ�����t�@�C����ǂݍ���
	void			Release();									//�T�E���h�n���h�����폜���A�ϐ��̏��������s���B
	int				Play(int PlayType, int TopPositionFlag);	//�ǂݍ��񂾉������Đ�����B
	int				Stop(void);									//�Đ����̉������~����
	int				Copy(const DxSound& original);				//���łɑ��݂���T�E���h�n���h���𕡐�����B���ʂ��R�s�[����B
	bool			CheckPraying(void);							//�Đ��������`�F�b�N����B
	int				SetLoopPos(int LoopTime);					//���[�v�Đ��̂��߂Ƀ��[�v�ʒu�����肷��B�i�~���b�P�ʁj
	int				SetLoopSamplePos(int LoopSamplePosition);	//���[�v�Đ��̂��߂Ƀ��[�v�ʒu�����肷��B�i�T���v�����P�ʁj

	static	void	SetMasterVolume(int volume);				//�}�X�^�[�{�����[����ݒ肷��B
//�ȉ��A�ϐ��̐ݒ��擾�p��inline�֐�
	//�O���t�B�b�N�n���h��
	inline	int		GetHandle() const {return Handle;}
	//����
	inline	void	SetVolume(int volume){if((Volume = volume) < 0)Volume = 0;if(Volume > 255)Volume = 255; ChangeVolumeSoundMem( Volume * MasterVolume / 255 , Handle);}
	inline	int		GetVolume() const {return Volume;}
	//�}�X�^�[����
	inline	static	int		GetMasterVolume() {return MasterVolume;}

};