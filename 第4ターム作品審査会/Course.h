#pragma once

#include<stdlib.h>
#include"BmpImage.h"
#include"glut.h"

//-------------------------------------
//コースの情報

class Course{
public:
	int m_width;
	int m_height;
	GLuint m_handle;//コースのテクスチャを格納する

	

	void draw();

	Course() :
		m_width(128),
		m_height(128),
		m_handle(0)
	{};

};

extern Course *testCourse;