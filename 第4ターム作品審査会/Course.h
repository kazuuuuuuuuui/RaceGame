#pragma once

//必ず使用するテクスチャの縦横とサイズを合わせること
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//ゴールに必要なコースの周回数
#define LAP_MAX (3)

#include<stdlib.h>
#include"BmpImage.h"
#include"glut.h"

//-------------------------------------
//コースの各ピクセルの情報

enum {
	PATH = 0,
	DART,
	START,
	GOAL,
	CHECK_FLONT,
	CHECK_BEHIND,
};



//-------------------------------------
//コースの情報

class Course{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];//各コースの各ピクセルの情報を格納するバッファ
	GLuint m_handle;//コースのテクスチャを格納する

	void draw();

	Course() :
		m_width(COURSE_WIDTH),
		m_height(COURSE_HEIGHT),
		m_handle(0)
	{
		//バッファの初期化
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}
	};

};

extern Course *testCourse;