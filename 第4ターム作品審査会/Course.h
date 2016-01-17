#pragma once

//�K���g�p����e�N�X�`���̏c���ƃT�C�Y�����킹�邱��
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//�R�[�X�����ɕK�v�ȃe�N�X�`���̖���
//�R�[�X���̂̃e�N�X�`���Ɣw�i�̃e�N�X�`����2��
#define COURSE_TEXTURE_NUMBER (2)

//�e�N�X�`���n���h���A�N�Z�X���Ɏg�p
#define COUSE_TEXTURE (0)
#define BACKGROUND_TEXTURE (1)

//�S�[���ɕK�v�ȃR�[�X�̎���
#define LAP_MAX (3)

#include<stdlib.h>
#include"MagicStone.h"
#include"BmpImage.h"
#include"glut.h"

//-------------------------------------
//�R�[�X�̊e�s�N�Z���̏��

enum {
	PATH = 0,
	DART,
	START,
	GOAL,
	CHECK_FLONT,
	CHECK_BEHIND,
	ITEMPOSITION,
};



//-------------------------------------
//�R�[�X�̏��

class Course{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];//�e�R�[�X�̊e�s�N�Z���̏����i�[����o�b�t�@
	GLuint m_handle[COURSE_TEXTURE_NUMBER];//[0]�ɂ̓R�[�X��[1]�ɂ͔w�i�̃e�N�X�`�����i�[����

	void draw();
	void setMagicStone();

	Course() :
		m_width(COURSE_WIDTH),
		m_height(COURSE_HEIGHT)
	{
		//�e�N�X�`���n���h���̏�����
		for (int i = 0; i < COURSE_TEXTURE_NUMBER; i++){
			m_handle[i] = 0;
		}

		//�R�[�X�o�b�t�@�̏�����
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}
	};

};

extern Course *testCourse;