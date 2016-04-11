//debug
#include<iostream>

#include<assert.h>
#include"SoundManager.h"

namespace oka
{
	SoundManager* SoundManager::m_instance = nullptr;
	
	//-------------------------------------
	//AL�̏���������
	//�f�o�C�X�̎擾�ƃR���e�L�X�g�̍쐬������

	void SoundManager::init()
	{
		ALCdevice *device = alcOpenDevice(NULL);
		assert(alcGetError(device) == ALC_NO_ERROR);

		ALCcontext *context;
		context = alcCreateContext(device, NULL);
		assert(alcGetError(device) == ALC_NO_ERROR);

		alcMakeContextCurrent(context);
		assert(alcGetError(device) == ALC_NO_ERROR);
	}


	//--------------------------------------------
	//�V���O���g���ɂ��邽�߂ɃC���X�^���X��
	//��������Ă��Ȃ���΃C���X�^���X�𐶐���
	//���ɃC���X�^���X����������Ă���΂��̃C���X�^���X��Ԃ�

	SoundManager* SoundManager::GetInstance() {

		if (nullptr == m_instance) 
		{
			m_instance = new SoundManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//������key��Sound�^��value���󂯎����
	//�����o��map�Ɋ��ɓo�^����Ă��邩�`�F�b�N��
	//�o�^����Ă��Ȃ���Βǉ�����

	void SoundManager::AddSound(const std::string _str, unsigned int _sound)
	{
		if (m_sounds.find(_str)==m_sounds.end())
		{
			//debug
			std::cout << "*Sound " << _str << "��ǉ����܂���\n";

			m_sounds.insert(std::make_pair(_str, _sound));
		}
		else
		{
			
		}
	}

	//-------------------------------------
	//�����Ƃ��Ď󂯎����key��map�ɓo�^����Ă��邩
	//�������o�^����Ă���΂���key�ɑΉ�����e�N�X�`���n���h����Ԃ�

	unsigned int SoundManager::GetHandle(const std::string _str)const
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			//�v�C��
			return 0;
		}
		else
		{
			return m_sounds.find(_str)->second;
		}
	}


	//-------------------------------------
	//������key��Sound�^��value���󂯎����
	//�����o��map�Ɋ��ɓo�^����Ă��邩�`�F�b�N��
	//�o�^����Ă����map���珜�O��delete����

	//�g���Ƃ��v����

	void SoundManager::DeleteSound(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			
		}
		else
		{
			//debug
			std::cout << "*Sound " << _str << "�͍폜����܂���\n";

			m_sounds.erase(_str);
		}
	}

	//-------------------------------------
	//���̍Đ�

	void SoundManager::Play(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
	
		}
		else
		{
			alSourcePlay(m_sounds[_str]);
		}
	}


	//-------------------------------------
	//���̒�~

	void SoundManager::Stop(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{

		}
		else
		{
			alSourceStop(m_sounds[_str]);
		}
		
	}

	//-------------------------------------
	//���ʂ̒���

	void SoundManager::ChangeVolume(const std::string _str,const float _value)
	{
		alSourcef(m_sounds[_str], AL_GAIN, _value);

	}

	//-------------------------------------
	//���K�̕ύX
	void SoundManager::ChangePitch(const std::string _str, const float _value)
	{
		alSourcef(m_sounds[_str], AL_PITCH, _value);

	}

}//namespace oka