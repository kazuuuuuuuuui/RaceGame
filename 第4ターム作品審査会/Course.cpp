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
		glBindTexture(GL_TEXTURE_2D, m_handle[COUSE_TEXTURE]);

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

				item[itemNum]->m_position.x = t;
				item[itemNum]->m_position.y = 0.5f;
				item[itemNum]->m_position.z = i - COURSE_HEIGHT;

				itemNum++;

			}

		}
	}

}

//取り敢えず
Course* createCourse(){

	Course *newCourse = nullptr;
	newCourse = new Course();

	//コースによって異なる部分
	//コース1(仮)
	//debug
	if (COURSE1 == selectedCourse){

		//チェックポイントの位置設定
		newCourse->m_checkPoint[0].m_position = { 57.f, 0.5f, -241.f };
		newCourse->m_checkPoint[1].m_position = { 140.f, 0.5f, -156.5f };
		newCourse->m_checkPoint[2].m_position = { 201.f, 0.5f, -231.5f };
		newCourse->m_checkPoint[3].m_position = { 238.5f, 0.5f, -195.f };
		newCourse->m_checkPoint[4].m_position = { 185.f, 0.5f, -122.f };
		newCourse->m_checkPoint[5].m_position = { 89.f, 0.5f, -97.5f };
		newCourse->m_checkPoint[6].m_position = { 160.5f, 0.5f, -74.5f };
		newCourse->m_checkPoint[7].m_position = { 236.f, 0.5f, -37.f };
		newCourse->m_checkPoint[8].m_position = { 124.f, 0.5f, -35.f };
		newCourse->m_checkPoint[9].m_position = { 23.5f, 0.5f, -89.5f };


		//AIポイントの位置設定
		newCourse->m_AIPoint[0].m_position = { 22.5f, 0.5f, -195.f };
		newCourse->m_AIPoint[1].m_position = { 40.f, 0.5f, -240.f };
		newCourse->m_AIPoint[2].m_position = { 72.f, 0.5f, -240.f };
		newCourse->m_AIPoint[3].m_position = { 91.f, 0.5f, -200.5f };
		newCourse->m_AIPoint[4].m_position = { 115.f, 0.5f, -159.f };
		newCourse->m_AIPoint[5].m_position = { 135.f, 0.5f, -155.f };
		newCourse->m_AIPoint[6].m_position = { 160.f, 0.5f, -163.5f };
		newCourse->m_AIPoint[7].m_position = { 174.f, 0.5f, -173.f };
		newCourse->m_AIPoint[8].m_position = { 186.f, 0.5f, -229.f };
		newCourse->m_AIPoint[9].m_position = { 208.f, 0.5f, -230.5f };
		newCourse->m_AIPoint[10].m_position = { 225.f, 0.5f, -223.5f };
		newCourse->m_AIPoint[11].m_position = { 233.5f, 0.5f, -205.f };
		newCourse->m_AIPoint[12].m_position = { 242.f, 0.5f, -175.5f };
		newCourse->m_AIPoint[13].m_position = { 237.f, 0.5f, -142.f };
		newCourse->m_AIPoint[14].m_position = { 207.f, 0.5f, -124.f };
		newCourse->m_AIPoint[15].m_position = { 108.f, 0.5f, -112.f };
		newCourse->m_AIPoint[16].m_position = { 91.f, 0.5f, -88.f };
		newCourse->m_AIPoint[17].m_position = { 180.f, 0.5f, -73.5f };
		newCourse->m_AIPoint[18].m_position = { 237.f, 0.5f, -48.f };
		newCourse->m_AIPoint[19].m_position = { 233.f, 0.5f, -15.f };
		newCourse->m_AIPoint[20].m_position = { 186.f, 0.5f, -8.5f };
		newCourse->m_AIPoint[21].m_position = { 146.f, 0.5f, -35.f };
		newCourse->m_AIPoint[22].m_position = { 99.f, 0.5f, -27.f };
		newCourse->m_AIPoint[23].m_position = { 57.f, 0.5f, -14.f };
		newCourse->m_AIPoint[24].m_position = { 27.f, 0.5f, -56.f };

		newCourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1/course1.bmp");
		BmpImage::makeBuffer("bmp/course1/buffer1.bmp", newCourse->m_buffer);
	}
	//

	//コース2(仮)
	else if (COURSE2 == selectedCourse){
		newCourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course2/course2.bmp");
		BmpImage::makeBuffer("bmp/course2/buffer2.bmp", newCourse->m_buffer);

		//チェックポイントの位置設定
		newCourse->m_checkPoint[0].m_position = { 40.f, 0.5f, -213.f };
		newCourse->m_checkPoint[1].m_position = { 136.f, 0.5f, -205.f };
		newCourse->m_checkPoint[2].m_position = { 213.f, 0.5f, -182.5f };
		newCourse->m_checkPoint[3].m_position = { 227.f, 0.5f, -114.f };
		newCourse->m_checkPoint[4].m_position = { 222.f, 0.5f, -36.f };
		newCourse->m_checkPoint[5].m_position = { 142.f, 0.5f, -62.5f };
		newCourse->m_checkPoint[6].m_position = { 117.f, 0.5f, -88.5f };
		newCourse->m_checkPoint[7].m_position = { 80.f, 0.5f, -56.5f };
		newCourse->m_checkPoint[8].m_position = { 48.f, 0.5f, -20.5f };
		newCourse->m_checkPoint[9].m_position = { 30.f, 0.5f, -54.5f };

		//AIポイントの位置設定
		newCourse->m_AIPoint[0].m_position = { 31.5f, 0.5f, -143.f };
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
		newCourse->m_AIPoint[24].m_position = { 30.f, 0.5f, -80.5f };

	}

	newCourse->setItem();

	return newCourse;

}
