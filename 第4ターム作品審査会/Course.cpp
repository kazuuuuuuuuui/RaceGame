#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"Course.h"
#include"CourseFlag.h"


Course *course = nullptr;

//選択されてるコース
int selectedCourse = COURSE1;


//-------------------------------------
//コース側で毎フレーム行う処理

void Course::update(){
}



//-------------------------------------
//各コース全体と空の描画

void Course::draw(){

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

				item[itemNum]->transform.m_position.x = t;
				item[itemNum]->transform.m_position.y = 0.5f;
				item[itemNum]->transform.m_position.z = i - COURSE_HEIGHT;

				itemNum++;

			}

		}
	}

}

//-------------------------------------
//選択されたコースにチェックポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::setCheckPoint(const char *_txtName) {

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < CHECK_POINT_NUMBER; i++) {

		glm::vec3 pos;
		fscanf(fp, "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_checkPoint[i].m_position = pos;

	}

}

//-------------------------------------
//選択されたコースにAI制御用のポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::setAIPoint(const char *_txtName) {

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < AI_POINT_NUMBER; i++) {

		glm::vec3 pos;
		fscanf(fp, "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_AIPoint[i].m_position = pos;

	}

}




//-------------------------------------
//選ばれたコースの生成
//チェックポイント・AI制御用のポイント・バッファ生成
//使用するテクスチャの読み込みを行う

Course* createCourse(){

	Course *newCourse = new Course();

	if (COURSE1 == selectedCourse){

		//チェックポイントの位置設定
		newCourse->setCheckPoint("txt/course1_cp.txt");
		
		//AIポイントの位置設定
		newCourse->setAIPoint("txt/course1_AIp.txt");

		//使用するテクスチャの読み込み
		newCourse->m_handle = BmpImage::loadImage("bmp/course1/course1.bmp");

		//バッファの作成
		BmpImage::makeBuffer("bmp/course1/buffer1.bmp", newCourse->m_buffer);
	}
	

	//コース2(仮)
	else if (COURSE2 == selectedCourse){

		//チェックポイントの位置設定
		newCourse->setCheckPoint("txt/course2_cp.txt");

		//AIポイントの位置設定
		newCourse->setAIPoint("txt/course2_AIp.txt");

	/*	newCourse->m_AIPoint[0].m_position = { 31.5f, 0.5f, -143.f };
		newCourse->m_AIPoint[1].m_position = { 32.f, 0.5f, -181.5f };
		newCourse->m_AIPoint[2].m_position = { 42.f, 0.5f, -206.5f };
		newCourse->m_AIPoint[3].m_position = { 54.5f, 0.5f, -216.5f };
		newCourse->m_AIPoint[4].m_position = { 70.5f, 0.5f, -222.5f };
		newCourse->m_AIPoint[5].m_position = { 100.f, 0.5f, -216.f };
		newCourse->m_AIPoint[6].m_position = { 137.5f, 0.5f, -203.f };
		newCourse->m_AIPoint[7].m_position = { 195.f, 0.5f, -194.f };
		newCourse->m_AIPoint[8].m_position = { 215.f, 0.5f, -180.f };
		newCourse->m_AIPoint[9].m_position = { 224.f, 0.5f, -164.5f };
		newCourse->m_AIPoint[10].m_position = { 226.f, 0.5f, -113.f };
		newCourse->m_AIPoint[11].m_position = { 230.f, 0.5f, -96.5f };
		newCourse->m_AIPoint[12].m_position = { 229.f, 0.5f, -45.f };
		newCourse->m_AIPoint[13].m_position = { 200.f, 0.5f, -25.5f };
		newCourse->m_AIPoint[14].m_position = { 163.f, 0.5f, -33.5f };
		newCourse->m_AIPoint[15].m_position = { 147.f, 0.5f, -54.f };
		newCourse->m_AIPoint[16].m_position = { 136.f, 0.5f, -75.5f };
		newCourse->m_AIPoint[17].m_position = { 121.f, 0.5f, -85.5f };
		newCourse->m_AIPoint[18].m_position = { 105.f, 0.5f, -81.5f };
		newCourse->m_AIPoint[19].m_position = { 84.f, 0.5f, -60.f };
		newCourse->m_AIPoint[20].m_position = { 85.f, 0.5f, -54.5f };
		newCourse->m_AIPoint[21].m_position = { 65.f, 0.5f, -29.f };
		newCourse->m_AIPoint[22].m_position = { 45.f, 0.5f, -16.5f };
		newCourse->m_AIPoint[23].m_position = { 31.f, 0.5f, -28.5f };
		newCourse->m_AIPoint[24].m_position = { 30.f, 0.5f, -80.5f };*/

		//使用するテクスチャの読み込み
		newCourse->m_handle = BmpImage::loadImage("bmp/course2/course2.bmp");
		
		//バッファの作成
		BmpImage::makeBuffer("bmp/course2/buffer2.bmp", newCourse->m_buffer);

	}

	newCourse->setItem();

	return newCourse;

}
