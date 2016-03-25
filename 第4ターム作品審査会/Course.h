#ifndef COURSE_H_
#define COURSE_H_

//必ず使用するテクスチャの縦横とサイズを合わせること
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//コースに配置されている魔石の数
#define SET_ITEM_NUMBER (20)

//コースに設置してある
//周回判定用のチェックポイントの個数
#define CHECK_POINT_NUMBER (10)

//コースに設置してある
//敵キャラAI用のポイントの個数
#define AI_POINT_NUMBER (25)

#include<stdlib.h>
#include"Item.h"
#include"BmpImage.h"
#include"CourseFlag.h"
#include"GameObject.h"
#include"AIFlag.h"
#include"Sound.h"
#include"glut.h"

//-------------------------------------
//コースの種類
enum
{
	COURSE1 = 0,
	COURSE2,
	COURSE_NUM_MAX
};


//-------------------------------------
//コースの各ピクセルの情報

enum 
{
	PATH = 0,
	DART,
	START,
	GOAL,
	ITEMPOSITION
};


//-------------------------------------
//コースの情報

class Course :public oka::GameObject 
{
public:
	int m_width;
	int m_height;
	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];   //各コースの各ピクセルの情報を格納するバッファ
	unsigned int m_handle;							 //コースのテクスチャ
	CourseFlag m_checkPoint[CHECK_POINT_NUMBER]; //周回判定用のポイント
	AIFlag m_AIPoint[AI_POINT_NUMBER];			 //敵AI用のポイント

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
		//コースバッファの初期化
		for (int i = 0; i < COURSE_HEIGHT; i++){
			for (int t = 0; t < COURSE_WIDTH; t++){
				m_buffer[i][t] = PATH;
			}
		}
	};

};

Course* createCourse();
extern int selectedCourse;

#endif

