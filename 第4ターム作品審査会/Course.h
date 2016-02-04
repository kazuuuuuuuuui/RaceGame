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

//�R�[�X�ɔz�u����Ă��閂�΂̐�
#define SET_ITEM_NUMBER (20)

//�R�[�X�ɐݒu���Ă���
//���񔻒�p�̃`�F�b�N�|�C���g�̌�
#define CHECK_POINT_NUMBER (10)

//�R�[�X�ɐݒu���Ă���
//�G�L����AI�p�̃|�C���g�̌�
#define AI_POINT_NUMBER (25)

//�S�[���ɕK�v�ȃR�[�X�̎���
#define LAP_MAX (3)

#include<stdlib.h>
#include"Item.h"
#include"BmpImage.h"
#include"CourseFlag.h"
#include"AIFlag.h"
#include"glut.h"

//-------------------------------------
//�R�[�X�̎��
enum{
	COURSE1 = 0,
	COURSE2,
	COURSE_NUM_MAX
};


//-------------------------------------
//�R�[�X�̊e�s�N�Z���̏��

enum {
	PATH = 0,
	DART,
	START,
	GOAL,
	ITEMPOSITION
};



//-------------------------------------
//�R�[�X�̏��

class Course{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];//�e�R�[�X�̊e�s�N�Z���̏����i�[����o�b�t�@
	GLuint m_handle[COURSE_TEXTURE_NUMBER];//[0]�ɂ̓R�[�X��[1]�ɂ͔w�i�̃e�N�X�`�����i�[����
	CourseFlag m_checkPoint[CHECK_POINT_NUMBER];//���񔻒�p�̃|�C���g
	AIFlag m_AIPoint[AI_POINT_NUMBER];//�GAI�p�̃|�C���g


	void draw();
	void update();
	void setItem();

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

Course* createCourse();
extern int selectedCourse;
extern Course *course;

