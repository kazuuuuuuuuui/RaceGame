#pragma once

#include<stdlib.h>
#include"BmpImage.h"
#include"glut.h"

//-------------------------------------
//�R�[�X�̏��

class Course{
public:
	int m_width;
	int m_height;
	GLuint m_handle;//�R�[�X�̃e�N�X�`�����i�[����

	

	void draw();

	Course() :
		m_width(128),
		m_height(128),
		m_handle(0)
	{};

};

extern Course *testCourse;