#include "DxLib.h"
#include "DisposableSound.h"
using namespace std;

/************************************************ �֐��̎��� ************************************************/

/************************************************************************************************
�֐����FDisposableSound		(�R���X�g���N�^)
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@�ϐ��̏��������s���B
************************************************************************************************/
DisposableSound::DisposableSound()
{
	PauseFlag = false;
}

/************************************************************************************************
�֐����F~DisposableSound		(�f�X�g���N�^)
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@�g���̂ăT�E���h�C���X�^���X�������Ă��鎑�����������B
************************************************************************************************/
DisposableSound::~DisposableSound()
{
	//���ׂĂ̎������������
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Release();
		delete (*it);
	}
}

/************************************************************************************************
�֐����FAddSound
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@�n���ꂽ�T�E���h�N���X�𕡐����A�Đ����J�n����B���ʂ��R�s�[����B
************************************************************************************************/
int DisposableSound::AddSound(const DxSound& original)
{
	//�R�s�[�����T�E���h�n���h����ێ����Ă��Ȃ��Ȃ�΃G���[�I��
	if(original.GetHandle() == -1)return -1;

	//�V����DxSound�N���X�����A�R�s�[���𕡐�������
	DxSound* tempP = new DxSound(original);

	//�����Ɏ��s�����ꍇ��delete���ăG���[�I��
	if(tempP->GetHandle() == -1)
	{
		delete tempP;
		return -1;
	}
	//���X�g�Ƀv�b�V������
	SoundList.push_back(tempP);
	//�|�[�Y�t���O�������Ă��Ȃ��Ȃ�΍Đ�������B�Đ��`���̓o�b�N�O���E���h�Œ�
	if(!PauseFlag)
	{
		tempP->Play(DX_PLAYTYPE_BACK,TRUE);
	}
	return 0;
}

/************************************************************************************************
�֐����FCheck
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@�Đ����I�����Ă���T�E���h�����o��T���B���������ꍇ�͂����delete���Alist����폜����B
************************************************************************************************/
void DisposableSound::Check(void)
{
	//�|�[�Y���Ȃ炻�̂܂܏I��
	if(PauseFlag)return ;
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		//�Đ����łȂ������`�F�b�N����
		if((*it)->CheckPraying()==0)
		{
			delete (*it);	//�f�X�g���N�^���쓮����̂ŁA��delete�ł����Ȃ�
			//���X�g����폜���A�폜��̃C�e���[�^���󂯎��
			it = SoundList.erase(it);
		}
	}
}

/************************************************************************************************
�֐����FPause
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@���ׂẴT�E���h�̍Đ����ꎞ��~����B
************************************************************************************************/
void DisposableSound::Pause(void)
{
	//���łɃ|�[�Y�ς݂Ȃ炻�̂܂܏I��
	if(PauseFlag)return ;

	//���ׂẴT�E���h���~����
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Stop();
	}
	PauseFlag = true;
}

/************************************************************************************************
�֐����FReopening
���@���F�Ȃ�
�߂�l�F�Ȃ�
�@�@�\�F
�@���ׂẴT�E���h�̍Đ����ĊJ����B
************************************************************************************************/
void DisposableSound::Reopening(void)
{
	//���łɍĐ��ς݂Ȃ炻�̂܂܏I��
	if(!PauseFlag)return ;
	//���ׂẴT�E���h���Đ�����
	list<DxSound*>::iterator it;
	for(it = SoundList.begin(); it != SoundList.end(); it++)
	{
		(*it)->Play(DX_PLAYTYPE_BACK,FALSE);
	}
	PauseFlag = false;
}
