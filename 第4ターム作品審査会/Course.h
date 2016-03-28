#ifndef COURSE_H_
#define COURSE_H_

//�K���g�p����e�N�X�`���̏c���ƃT�C�Y�����킹�邱��
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//�R�[�X�ɔz�u����Ă��閂�΂̐�
#define SET_ITEM_NUMBER (20)

//�R�[�X�ɐݒu���Ă���
//���񔻒�p�̃`�F�b�N�|�C���g�̌�
#define CHECK_POINT_NUMBER (10)

//�R�[�X�ɐݒu���Ă���
//�G�L����AI�p�̃|�C���g�̌�
#define AI_POINT_NUMBER (25)

#include<stdlib.h>
#include"Item.h"
#include"BmpImage.h"
#include"CourseFlag.h"
#include"GameObject.h"
#include"AIFlag.h"
#include"Sound.h"
#include"Vec3.h"
#include"glut.h"

//-------------------------------------
//�R�[�X�̎��
enum
{
	COURSE1 = 0,
	COURSE2,
	COURSE_NUM_MAX
};


//-------------------------------------
//�R�[�X�̊e�s�N�Z���̏��

enum 
{
	PATH = 0,
	DART,
	START,
	GOAL,
	ITEMPOSITION
};


//-------------------------------------
//�R�[�X�̏��

class Course :public oka::GameObject 
{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];   //�e�R�[�X�̊e�s�N�Z���̏����i�[����o�b�t�@
	unsigned int m_handle;							 //�R�[�X�̃e�N�X�`��
	CourseFlag m_checkPoint[CHECK_POINT_NUMBER]; //���񔻒�p�̃|�C���g
	AIFlag m_AIPoint[AI_POINT_NUMBER];			 //�GAI�p�̃|�C���g
	oka::Vec3 m_backgroundColor;

	void Draw();
	void Update() {};
	void setItem();
	void setCheckPoint(const char *_txtName);
	void setAIPoint(const char *_txtName);

	Course() :
		m_width(COURSE_WIDTH),
		m_height(COURSE_HEIGHT),
		m_handle(0)
	{	
		//�R�[�X�o�b�t�@�̏�����
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}

		//�w�i�F������
		oka::Vec3 color;
		color.m_x = 77.0f / 255.0f;
		color.m_y = 180.0f / 255.0f;
		color.m_z = 232.0f / 255.0f;

		m_backgroundColor = color;

	};

};

Course* createCourse();
extern int selectedCourse;

#endif

