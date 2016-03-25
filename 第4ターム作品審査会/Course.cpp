#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"Course.h"
#include"CourseFlag.h"
#include"ItemManager.h"

//選択されてるコース
int selectedCourse = COURSE1;

//-------------------------------------
//各コース全体と空の描画

void Course::Draw(){

	glEnable(GL_TEXTURE_2D);

	//コースの描画
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glColor3f(1, 1, 1);

		glBegin(GL_QUADS);
		{
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(0.f, 0.f, 0.f);

			glTexCoord2f(1.f, 1.f);
			glVertex3f(m_width, 0.f, 0.f);

			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_width, 0, -m_height);

			glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, -m_height);
		}
		glEnd();

	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

//-------------------------------------
//コース上に魔石を配置する
//画像左上から右下に向かって読んでいく

void Course::setItem(){

	for (int i = 0; i < COURSE_HEIGHT; i++){
		for (int t = 0; t < COURSE_WIDTH; t++){

			if (ITEMPOSITION == m_buffer[i][t]){

				//取り敢えず
				oka::Vec3 position;
				position.m_x = t;
				position.m_y = 0.5f;
				position.m_z = i - COURSE_HEIGHT;

				ItemManager::GetInstance()->m_item[itemNum]->m_transform.SetPosition(position);

				itemNum++;

			}

		}
	}

}

//-------------------------------------
//選択されたコースにチェックポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::setCheckPoint(const char *_txtName) 
{

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < CHECK_POINT_NUMBER; i++) 
	{
		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_checkPoint[i].m_position = position;

	}

}

//-------------------------------------
//選択されたコースにAI制御用のポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::setAIPoint(const char *_txtName) 
{
	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < AI_POINT_NUMBER; i++) {

		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_AIPoint[i].m_position = position;

	}

}




//-------------------------------------
//選ばれたコースの生成
//チェックポイント・AI制御用のポイント・バッファ生成
//使用するテクスチャの読み込みを行う

Course* createCourse()
{

	Course *newCourse = new Course();

	if (COURSE1 == selectedCourse)
	{

		//チェックポイントの位置設定
		newCourse->setCheckPoint("txt/course1_cp.txt");
		
		//AIポイントの位置設定
		newCourse->setAIPoint("txt/course1_AIp.txt");

		//使用するテクスチャの読み込み
		newCourse->m_handle = oka::BmpImage::LoadImage3f("bmp/course1/course1.bmp");

		//バッファの作成
		oka::BmpImage::makeBuffer("bmp/course1/buffer1.bmp", newCourse->m_buffer);
	}
	

	//コース2(仮)
	else if (COURSE2 == selectedCourse)
	{

		//チェックポイントの位置設定
		newCourse->setCheckPoint("txt/course2_cp.txt");

		//AIポイントの位置設定
		newCourse->setAIPoint("txt/course2_AIp.txt");

		//使用するテクスチャの読み込み
		newCourse->m_handle = oka::BmpImage::LoadImage3f("bmp/course2/course2.bmp");
		
		//バッファの作成
		oka::BmpImage::makeBuffer("bmp/course2/buffer2.bmp", newCourse->m_buffer);

	}

	newCourse->setItem();

	return newCourse;

}
