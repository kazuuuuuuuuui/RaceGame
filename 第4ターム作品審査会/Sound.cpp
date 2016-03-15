#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
#include"WavFile.h"
#include"Sound.h"

//�G���W���̉�
unsigned char engine_sound[8] = { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char count_sound[8] = { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 };

//���[�X�J�n���̉�
Sound *startCountDown = nullptr;

//-------------------------------------
//AL�̏���������

void Sound::init(){

	//�f�o�C�X�̎擾
	ALCdevice *device = alcOpenDevice(NULL);

	//�G���[�`�F�b�N
	assert(alcGetError(device) == ALC_NO_ERROR);

	//�R���e�L�X�g�̍쐬
	ALCcontext *context;
	context = alcCreateContext(
		device,//ALCdevice *device
		NULL//const ALCint* attrlist
		);
	assert(alcGetError(device) == ALC_NO_ERROR);

	alcMakeContextCurrent(context);
	assert(alcGetError(device) == ALC_NO_ERROR);

}


//-------------------------------------
//��`�g�̓ǂݍ���
void Sound::loadKukeiha(const unsigned char *data, int _size, ALsizei _freq){

	alGenBuffers(
		1,//ALsizei n,
		&m_bid);//ALuint *buffers
	assert(alGetError() == AL_NO_ERROR);

	alBufferData(
		m_bid,//ALuint buffer,
		AL_FORMAT_MONO8,//ALenum format,
		data,//const ALvoid *data,
		_size,//ALsizei size,
		_size * _freq);//ALsizei freq(���g��)

	assert(alGetError() == AL_NO_ERROR);

	alGenSources(
		1,//ALsizei n,
		&m_sid);//ALuint *sources
	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		m_sid,
		AL_BUFFER,
		m_bid);
	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		m_sid,
		AL_LOOPING,
		AL_TRUE);
	assert(alGetError() == AL_NO_ERROR);

}


//-------------------------------------
//wav�t�@�C���̓ǂݍ���

void Sound::loadWavFile(const char *_wavFileName){

		alGenBuffers(1, &m_bid);
		assert(alGetError() == AL_NO_ERROR);

		//�t�@�C���̓ǂݍ���
		WavFile wav;

		FILE *pFile = fopen(_wavFileName, "rb");
		assert(pFile != NULL);

		fread(&wav, sizeof(WavFile), 1, pFile);

		unsigned char *wav_data = (unsigned char*)malloc(sizeof(char)*wav.m_data_size);

		fread(wav_data, wav.m_data_size, 1, pFile);

		//���m����
		if (1 == wav.m_channel){

			//8bit
			if (8 == wav.m_bit){
				wav.m_format = AL_FORMAT_MONO8;
			}

			//16�r�b�g
			else if (16 == wav.m_bit){
				wav.m_format = AL_FORMAT_MONO16;
			}

		}

		//�X�e���I
		else if (2 == wav.m_channel){

			//8bit
			if (8 == wav.m_bit){
				wav.m_format = AL_FORMAT_STEREO8;
			}

			//16�r�b�g
			else if (16 == wav.m_bit){
				wav.m_format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(
			m_bid,
			wav.m_format,
			wav_data,
			wav.m_data_size,
			wav.m_rate);

		assert(alGetError() == AL_NO_ERROR);

		alGenSources(1, &m_sid);
		assert(alGetError() == AL_NO_ERROR);

		alSourcei(m_sid, AL_BUFFER, m_bid);
		assert(alGetError() == AL_NO_ERROR);

		fclose(pFile);
		free(wav_data);

}


//-------------------------------------
//���̍Đ�

void Sound::play(){

	alSourcePlay(m_sid);

}


//-------------------------------------
//���̒�~

void Sound::stop(){

	alSourceStop(m_sid);

}

//-------------------------------------
//��Ԃ̎擾

void Sound::checkState(){

	//alGetSourcei(m_sid, AL_SOURCE_STATE, &(int)m_bid);

}

//-------------------------------------
//���ʂ̒���

void Sound::changeVolume(float _value){

	alSourcef(m_sid, AL_GAIN, _value);

}