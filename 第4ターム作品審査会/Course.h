#pragma once

//�K���g�p����e�N�X�`���̏c���ƃT�C�Y�����킹�邱��
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//�S�[���ɕK�v�ȃR�[�X�̎���
#define LAP_MAX (3)

#include<stdlib.h>
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
};



//-------------------------------------
//�R�[�X�̏��

class Course{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];//�e�R�[�X�̊e�s�N�Z���̏����i�[����o�b�t�@
	GLuint m_handle;//�R�[�X�̃e�N�X�`�����i�[����

	void draw();

	Course() :
		m_width(COURSE_WIDTH),
		m_height(COURSE_HEIGHT),
		m_handle(0)
	{
		//�o�b�t�@�̏�����
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}
	};

};

extern Course *testCourse;