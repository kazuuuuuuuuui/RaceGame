#pragma once

#pragma comment(lib,"OpenAL32.lib")

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include"AL\alc.h"
#include"AL\al.h"

//wav�t�@�C���̍\��
struct WavFile
{
	char m_riff[4];              // = "RIFF"
	unsigned int m_file_size;    // �S�̃T�C�Y
	char m_fmt[8];               // "WAVEfmt "
	unsigned int m_fmt_size;      // fmt �`�����N�T�C�Y
	unsigned short  m_format;       // �t�H�[�}�b�g�̎��
	unsigned short  m_channel;      // �`�����l��
	unsigned int   m_rate;         // �T���v�����O���[�g
	unsigned int   m_avgbyte;      // rate * block
	unsigned short  m_block;        // channels * bit / 8
	unsigned short  m_bit;          // �r�b�g��
	char m_data[4];               // = "data"
	unsigned int m_data_size;      // �f�[�^�T�C�Y

};

