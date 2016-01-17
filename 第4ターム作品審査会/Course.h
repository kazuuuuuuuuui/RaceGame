#pragma once

//必ず使用するテクスチャの縦横とサイズを合わせること
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//コース生成に必要なテクスチャの枚数
//コース自体のテクスチャと背景のテクスチャの2枚
#define COURSE_TEXTURE_NUMBER (2)

//テクスチャハンドルアクセス時に使用
#define COUSE_TEXTURE (0)
#define BACKGROUND_TEXTURE (1)

//ゴールに必要なコースの周回数
#define LAP_MAX (3)

#include<stdlib.h>
#include"MagicStone.h"
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
	ITEMPOSITION,
};



//-------------------------------------
//コースの情報

class Course{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];//各コースの各ピクセルの情報を格納するバッファ
	GLuint m_handle[COURSE_TEXTURE_NUMBER];//[0]にはコースの[1]には背景のテクスチャを格納する

	void draw();
	void setMagicStone();

	Course() :
		m_width(COURSE_WIDTH),
		m_height(COURSE_HEIGHT)
	{
		//テクスチャハンドルの初期化
		for (int i = 0; i < COURSE_TEXTURE_NUMBER; i++){
			m_handle[i] = 0;
		}

		//コースバッファの初期化
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}
	};

};

extern Course *testCourse;