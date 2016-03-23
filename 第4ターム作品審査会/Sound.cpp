#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include"WavFile.h"
#include"Sound.h"

//�G���W���̉�
unsigned char engine_sound[8] = { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char count_sound[8] = { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 };

namespace oka
{

	//-------------------------------------
	//��`�g�̓ǂݍ���
	//�����Ƃ��Ĕg�`�f�[�^�E�g�`�f�[�^�̑傫���E���g�����󂯎��

	unsigned int Sound::LoadSquareWave(const unsigned char *data, int _size, int _freq)
	{
		unsigned int sid;
		unsigned int bid;

		alGenBuffers(1, &bid);
		assert(alGetError() == AL_NO_ERROR);

		alBufferData(bid,AL_FORMAT_MONO8,data,_size,_size * _freq);
		assert(alGetError() == AL_NO_ERROR);

		alGenSources(1,&sid);
		assert(alGetError() == AL_NO_ERROR);

		alSourcei(sid,AL_BUFFER,bid);
		assert(alGetError() == AL_NO_ERROR);

		alSourcei(sid,AL_LOOPING,AL_TRUE);
		assert(alGetError() == AL_NO_ERROR);

		return sid;
	}


	//-------------------------------------
	//wav�t�@�C���̓ǂݍ���
	//�����Ƃ���.wav�`���̃t�@�C�����O���󂯎��
	//�n���h��(ID)��Ԃ�

	unsigned int Sound::LoadWavFile(const char *_wavFileName)
	{
		unsigned int sid;
		unsigned int bid;

		alGenBuffers(1, &bid);

		WavFile wav;

		FILE *fp = fopen(_wavFileName, "rb");
		assert(fp != NULL);

		fread(&wav, sizeof(WavFile), 1, fp);

		unsigned char *data = (unsigned char*)malloc(sizeof(char)*wav.m_data_size);

		fread(data, wav.m_data_size, 1, fp);

		//���m����
		if (1 == wav.m_channel)
		{
			//8�r�b�g
			if (8 == wav.m_bit)
			{
				wav.m_format = AL_FORMAT_MONO8;
			}

			//16�r�b�g
			else if (16 == wav.m_bit)
			{
				wav.m_format = AL_FORMAT_MONO16;
			}
		}

		//�X�e���I
		else if (2 == wav.m_channel)
		{
			//8�r�b�g
			if (8 == wav.m_bit) {
				wav.m_format = AL_FORMAT_STEREO8;
			}
			//16�r�b�g
			else if (16 == wav.m_bit) {
				wav.m_format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(
			bid,
			wav.m_format,
			data,
			wav.m_data_size,
			wav.m_rate);

		assert(alGetError() == AL_NO_ERROR);

		alGenSources(1, &sid);
		assert(alGetError() == AL_NO_ERROR);

		alSourcei(sid, AL_BUFFER, bid);
		assert(alGetError() == AL_NO_ERROR);

		fclose(fp);
		free(data);

		return sid;
	}


	//-------------------------------------
	//�n���h�����󂯎���ĉ����Đ�����

	void Sound::Play(unsigned int _sound)
	{
		alSourcePlay(_sound);
	}

	//-------------------------------------
	//�n���h�����󂯎���ĉ����~����

	void Sound::Stop(unsigned int _sound)
	{
		alSourceStop(_sound);
	}

}//namespace oka