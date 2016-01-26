/*

順位判定
周回数→どのチェックポイントまで通過したか→次のチェックポイントまでの距離


*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<algorithm>
#include"GameManager.h"
#include"camera.h"
#include"player.h"
#include"Enemy.h"
#include"Course.h"
#include"CourseFlag.h"
#include"Item.h"
#include"StrokeString.h"
#include"FireEffect.h"
#include"glut.h"

/***********debug***********/

#define COURSE_TYPE (1)

Enemy *com1 = nullptr;
Enemy *com2 = nullptr;
Enemy *com3 = nullptr;

/**************************/


//レースが始まっているかのフラグ
bool startRace = false;

//debug
//bool startRace = true;

//-------------------------------------
//レーススタートのカウントダウン
//取り敢えず

int startFrame = 0;//フレーム数
int timenow = 0;//経過時間
int timebase = 0;//計測開始時間
int startCount = 6;


GLuint threeTexture = 0;
GLuint twoTexture = 0;
GLuint oneTexture = 0;
GLuint goTexture = 0;
GLuint goalTexture = 0;


GLuint rank1st = 0;
GLuint rank2nd = 0;
GLuint rank3rd = 0;
GLuint rank4th = 0;

//debug
float xx = 0.f;
float yy = 0.f;

//最初の3・2・1
void countRaceStart(){

	startFrame++; //フレーム数を＋１
	timenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	if (timenow - timebase > 1000)      //１秒以上たったら処理を行う
	{
		startCount--;

		if (0 == startCount){

			//カウントダウンが終了したら
			//レースが開始されているかのフラグを立てる
			startRace = true;

		}

		timebase = timenow;//基準時間を設定                
		startFrame = 0;//フレーム数をリセット
	}

}

void printRaceStart(){

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (startCount <= 3 && startCount > 0){
		glPushMatrix();
		{
			glTranslatef(100, 100, 0);

			if (startCount == 3){
				glBindTexture(GL_TEXTURE_2D, threeTexture);
			}
			else if (startCount == 2){
				glBindTexture(GL_TEXTURE_2D, twoTexture);
			}
			else if (startCount == 1){
				glBindTexture(GL_TEXTURE_2D, oneTexture);
			}

			glColor4f(1, 1, 1, 1);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 0);
				glVertex2f(0, 0);
				glTexCoord2f(1, 0);
				glVertex2f(100, 0);
				glTexCoord2f(1, 1);
				glVertex2f(100, 100);
				glTexCoord2f(0, 1);
				glVertex2f(0, 100);
			}
			glEnd();
		}
		glPopMatrix();

	}
	else if (0 == startCount){

		static float num = 1.f;
		num += 0.007f;

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, goTexture);

			glTranslatef(150, 150, 0);
			glScalef(num, num, num);
			glColor4f(1, 1, 1, 1);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 0);
				glVertex2f(-50, -50);
				glTexCoord2f(1, 0);
				glVertex2f(50, -50);
				glTexCoord2f(1, 1);
				glVertex2f(50, 50);
				glTexCoord2f(0, 1);
				glVertex2f(-50, 50);
			}
			glEnd();
		}
		glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}


//順位のテクスチャ描画
void printRanking(){

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//順位に応じて貼るテクスチャを変える
	switch (player->m_ranking){
	case 1:
		glBindTexture(GL_TEXTURE_2D, rank1st);
		break;

	case 2:
		glBindTexture(GL_TEXTURE_2D, rank2nd);
		break;

	case 3:
		glBindTexture(GL_TEXTURE_2D, rank3rd);
		break;

	case 4:
		glBindTexture(GL_TEXTURE_2D, rank4th);
		break;

	}

	glPushMatrix();
	{
		if (false == player->m_isGoal){
			glTranslatef(0.f, 0.f, 0);
		}
		else{
			glTranslatef(50.f, 193.f, 0);
		}

		glBegin(GL_QUADS);
		{
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(1, 0);
			glVertex2f(80, 0);
			glTexCoord2f(1, 1);
			glVertex2f(80, 80);
			glTexCoord2f(0, 1);
			glVertex2f(0, 80);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}


//-------------------------------------
//fps計測用変数と関数
int GLframe = 0; //フレーム数
int GLtimenow = 0;//経過時間
int GLtimebase = 0;//計測開始時間

void fps(){
	GLframe++; //フレーム数を＋１
	GLtimenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	if (GLtimenow - GLtimebase > 1000)      //１秒以上たったらfpsを出力
	{
		printf("fps:%f\r", GLframe*1000.0 / (GLtimenow - GLtimebase));
		GLtimebase = GLtimenow;//基準時間を設定                
		GLframe = 0;//フレーム数をリセット
	}
}

//-------------------------------------



//-------------------------------------
//キーボードからの入力全般

void keyboard(unsigned char key, int x, int y){

	//debug
	if ('d' == key){
		xx += 1.f;
	}
	else if ('a' == key){
		xx -= 1.f;
	}
	else if ('w' == key){
		yy += 1.f;
	}
	else if ('s' == key){
		yy -= 1.f;
	}


}


void specialkeydown(int key, int x, int y){

}



//debug
//GLuint koori = 0;

//取り敢えず
Course* createCourse(){

	Course *newcourse = nullptr;
	newcourse = new Course();



	//コースによって異なる部分
	//コース1(仮)
	//debug
	if (1 == COURSE_TYPE){
		//チェックポイントの位置設定
		newcourse->m_checkPoint[0].m_position = { 57.f, 0.5f, -241.f };
		newcourse->m_checkPoint[1].m_position = { 140.f, 0.5f, -156.5 };
		newcourse->m_checkPoint[2].m_position = { 172.f, 0.5f, -196.f };
		newcourse->m_checkPoint[3].m_position = { 238.5f, 0.5f, -195.f };
		newcourse->m_checkPoint[4].m_position = { 185.f, 0.5f, -122.f };
		newcourse->m_checkPoint[5].m_position = { 134.f, 0.5f, -116.5f };
		newcourse->m_checkPoint[6].m_position = { 160.5f, 0.5f, -74.5f };
		newcourse->m_checkPoint[7].m_position = { 236.f, 0.5f, -37.f };
		newcourse->m_checkPoint[8].m_position = { 124.f, 0.5f, -35.f };
		newcourse->m_checkPoint[9].m_position = { 23.5f, 0.5f, -89.5f };


		//AIポイントの位置設定
		newcourse->m_AIPoint[0].m_position = { 22.5f, 0.5f, -195.f };
		newcourse->m_AIPoint[1].m_position = { 40.f, 0.5f, -240.f };
		newcourse->m_AIPoint[2].m_position = { 72.f, 0.5f, -240.f };
		newcourse->m_AIPoint[3].m_position = { 91.f, 0.5f, -200.5f };
		newcourse->m_AIPoint[4].m_position = { 115.f, 0.5f, -159.f };
		newcourse->m_AIPoint[5].m_position = { 135.f, 0.5f, -155.f };
		newcourse->m_AIPoint[6].m_position = { 160.f, 0.5f, -163.5f };
		newcourse->m_AIPoint[7].m_position = { 174.f, 0.5f, -173.f };
		newcourse->m_AIPoint[8].m_position = { 186.f, 0.5f, -229.f };
		newcourse->m_AIPoint[9].m_position = { 208.f, 0.5f, -230.5f };
		newcourse->m_AIPoint[10].m_position = { 225.f, 0.5f, -223.5f };
		newcourse->m_AIPoint[11].m_position = { 233.5f, 0.5f, -205.f };
		newcourse->m_AIPoint[12].m_position = { 242.f, 0.5f, -175.5f };
		newcourse->m_AIPoint[13].m_position = { 237.f, 0.5f, -142.f };
		newcourse->m_AIPoint[14].m_position = { 207.f, 0.5f, -124.f };
		newcourse->m_AIPoint[15].m_position = { 108.f, 0.5f, -112.f };
		newcourse->m_AIPoint[16].m_position = { 91.f, 0.5f, -88.f };
		newcourse->m_AIPoint[17].m_position = { 180.f, 0.5f, -73.5f };
		newcourse->m_AIPoint[18].m_position = { 237.f, 0.5f, -48.f };
		newcourse->m_AIPoint[19].m_position = { 233.f, 0.5f, -15.f };
		newcourse->m_AIPoint[20].m_position = { 186.f, 0.5f, -8.5f };
		newcourse->m_AIPoint[21].m_position = { 146.f, 0.5f, -35.f };
		newcourse->m_AIPoint[22].m_position = { 99.f, 0.5f, -27.f };
		newcourse->m_AIPoint[23].m_position = { 57.f, 0.5f, -14.f };
		newcourse->m_AIPoint[24].m_position = { 27.f, 0.5f, -56.f };

		newcourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1/course1.bmp");
		//course->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/course1/background1.bmp");
		BmpImage::makeBuffer("bmp/course1/buffer1.bmp", newcourse->m_buffer);
	}
	//

	//コース2(仮)
	else if (2 == COURSE_TYPE){
		newcourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course2/course2.bmp");
		//course->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/course2/background2.bmp");
		BmpImage::makeBuffer("bmp/course2/buffer2.bmp", newcourse->m_buffer);
	}
	//

	newcourse->setItem();

	return newcourse;

}

//debug
//指定した座標と添え字のチェックポイントまでの距離を返す
float lengthCheckPoint(glm::vec3 _pos, int _point){

	float length = 0.f;
	glm::vec3 v;

	v.x = _pos.x - course->m_checkPoint[_point].m_position.x;
	v.y = _pos.y - course->m_checkPoint[_point].m_position.y;
	v.z = _pos.z - course->m_checkPoint[_point].m_position.z;

	length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);

	return length;

}

//順位判定用の関数
//順位の判定のみする
bool checkRanking(Character *_character1, Character *_character2){

	//周回数での判定
	if (_character1->m_lapCount > _character2->m_lapCount){
		return true;
	}
	else if (_character1->m_lapCount < _character2->m_lapCount){
		return false;
	}

	//チェックポイントの進み具合での判定
	if (_character1->m_nowPoint > _character2->m_nowPoint){
		return true;
	}
	else if (_character1->m_nowPoint < _character2->m_nowPoint){
		//return true;
		return false;
	}

	//目指しているチェックポイントへの距離での判定
	if (_character1->m_nextCheckPointLength > _character2->m_nextCheckPointLength){
		return false;
	}
	else if (_character1->m_nextCheckPointLength < _character2->m_nextCheckPointLength){
		return true;
	}

	//取り敢えず何か返す
	return false;

}

//-------------------------------------
//ゲームの初期化全般を行う

//後で書き換え
xFile body;
xFile backWheel;

void init(){

	srand(time(NULL));

	//モデルデータの読み込み
	xFile::loadXfile("xFile/testbike.x", body);
	xFile::loadXfile("xFile/taiya.x", backWheel);


	//後で書き換え
	//プレイヤーの生成
	player = new Player();
	player->m_position = { 12.f, 0.5f, -160.f };

	player->m_frontPosition.x = player->m_position.x - sin(player->m_rotate.y)*1.55f;
	player->m_frontPosition.y = 1.f;
	player->m_frontPosition.z = player->m_position.z - cos(player->m_rotate.y)*1.55f;

	player->m_backPosition.x = player->m_position.x + sin(player->m_rotate.y)*1.15f;
	player->m_backPosition.y = 1.f;
	player->m_backPosition.z = player->m_position.z + cos(player->m_rotate.y)*1.15f;

	player->m_body = body;
	player->m_backWheel = backWheel;

	//敵の生成
	com1 = new Enemy();
	com1->m_position = { 15.f, 0.5f, -150.f };

	com1->m_frontPosition.x = com1->m_position.x - sin(com1->m_rotate.y)*1.55f;
	com1->m_frontPosition.y = 1.f;
	com1->m_frontPosition.z = com1->m_position.z - cos(com1->m_rotate.y)*1.55f;

	com1->m_backPosition.x = com1->m_position.x + sin(com1->m_rotate.y)*1.15f;
	com1->m_backPosition.y = 1.f;
	com1->m_backPosition.z = com1->m_position.z + cos(com1->m_rotate.y)*1.15f;

	com1->m_body = body;
	com1->m_backWheel = backWheel;

	//
	com2 = new Enemy();
	com2->m_position = { 20.f, 0.5f, -140.f };

	com2->m_frontPosition.x = com2->m_position.x - sin(com2->m_rotate.y)*1.55f;
	com2->m_frontPosition.y = 1.f;
	com2->m_frontPosition.z = com2->m_position.z - cos(com2->m_rotate.y)*1.55f;

	com2->m_backPosition.x = com2->m_position.x + sin(com2->m_rotate.y)*1.15f;
	com2->m_backPosition.y = 1.f;
	com2->m_backPosition.z = com2->m_position.z + cos(com2->m_rotate.y)*1.15f;

	com2->m_body = body;
	com2->m_backWheel = backWheel;

	//
	com3 = new Enemy();
	com3->m_position = { 25.f, 0.5f, -130.f };

	com3->m_frontPosition.x = com3->m_position.x - sin(com3->m_rotate.y)*1.55f;
	com3->m_frontPosition.y = 1.f;
	com3->m_frontPosition.z = com3->m_position.z - cos(com3->m_rotate.y)*1.55f;

	com3->m_backPosition.x = com3->m_position.x + sin(com3->m_rotate.y)*1.15f;
	com3->m_backPosition.y = 1.f;
	com3->m_backPosition.z = com3->m_position.z + cos(com3->m_rotate.y)*1.15f;

	com3->m_body = body;
	com3->m_backWheel = backWheel;

	//生成したプレイヤーと敵をベクターで管理
	character.push_back(player);
	character.push_back(com1);
	character.push_back(com2);
	character.push_back(com3);

	//カメラの生成
	camera = new Camera();

	//アイテム生成→コースの生成→アイテムの設置

	//アイテムの生成
	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i] = new Item();
	}

	//後で書き換え
	//コースの生成
	course = createCourse();

	//テクスチャの読み込み
	//透過度無し



	//透過度有り
	threeTexture = BmpImage::loadImage_alpha("bmp/start/three.bmp");
	twoTexture = BmpImage::loadImage_alpha("bmp/start/two.bmp");
	oneTexture = BmpImage::loadImage_alpha("bmp/start/one.bmp");
	goTexture = BmpImage::loadImage_alpha("bmp/start/go.bmp");
	goalTexture = BmpImage::loadImage_alpha("bmp/goal.bmp");

	smoke_handle = BmpImage::loadImage_alpha("bmp/Effect/smoke.bmp");

	rank1st = BmpImage::loadImage_alpha("bmp/Ranking/1st.bmp");
	rank2nd = BmpImage::loadImage_alpha("bmp/Ranking/2nd.bmp");
	rank3rd = BmpImage::loadImage_alpha("bmp/Ranking/3rd.bmp");
	rank4th = BmpImage::loadImage_alpha("bmp/Ranking/4th.bmp");

	//koori = BmpImage::loadImage_alpha("bmp/Effect/blizzard.bmp");

	//使用する魔石のテクスチャ読み込み
	fire_handle = BmpImage::loadImage("bmp/MagicStone/ms_fire.bmp");
	blizzard_handle = BmpImage::loadImage("bmp/MagicStone/ms_blizzard.bmp");

	//最初の順位設定と順位付与
	for (unsigned int i = 0; i < character.size(); i++){
		std::sort(character.begin(), character.end(), checkRanking);
	}

	for (unsigned int i = 0; i < character.size(); i++){
		character[i]->m_ranking = i + 1;
	}

	//後で書き換え
	sprintf_s(player->m_str_lapTime[FIRST], "%02d:%02d:%03d ", player->m_minute[FIRST], player->m_second[FIRST], player->m_milliSecond[FIRST]);
	sprintf_s(player->m_str_lapTime[SECOND], "%02d:%02d:%03d ", player->m_minute[SECOND], player->m_second[SECOND], player->m_milliSecond[SECOND]);
	sprintf_s(player->m_str_lapTime[THIRD], "%02d:%02d:%03d ", player->m_minute[THIRD], player->m_second[THIRD], player->m_milliSecond[THIRD]);
}


//-------------------------------------
//プレイヤーの制御
unsigned int pressedKeys = 0;//現フレーム押されているキー
unsigned int releasedKeys = 0;//現フレーム押されていないキー
unsigned int lastkeys = 0;//前フレーム前に押されていたキー
unsigned int changedKeys = 0;//前フレームと現フレームで変化があったキー
unsigned int downkeys = 0;

void joystick(unsigned int buttonMask, int x, int y, int z){
	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	pressedKeys = buttonMask;
	releasedKeys = ~pressedKeys;
	changedKeys = pressedKeys ^ lastkeys;
	downkeys = pressedKeys & changedKeys;

	if (true == startRace){

		//-1000～1000の値を-1～1の値に変換して引数として渡す
		player->control(pressedKeys, downkeys, (float)x / 1000.f, (float)y / 1000.f, (float)z / 1000.f);

	}


	lastkeys = buttonMask;
}

//取り敢えず
int flame = 0;
int milliSecond = 0;
int second = 0;
int minute = 0;

//時間表示に使う
char str_time[256];

//周回数表示に使う
char str_lapCount[256];
char str_lapMax[256];

int getMilliSecond(int _flame){
	return ((_flame * 1000) / 60) % 1000;
}

int getSecond(int _flame){
	return _flame / 60;
}

int getMinute(int _second){
	return _second / 60;
}


//接触判定
//取り敢えず
bool isHitCharacter(Character *_my, Character *_you){

	//自分の前輪と相手の前輪とのベクトル
	glm::vec3 front_front;

	//自分の後輪と相手の後輪とのベクトル
	glm::vec3 back_back;

	//自分の後輪と相手の後輪とのベクトル
	glm::vec3 front_back;

	//自分の後輪と相手の後輪とのベクトル
	glm::vec3 back_front;

	//自分の前輪と相手の中心座標とのベクトル
	glm::vec3 front_body;

	//自分の後輪と相手の中心座標とのベクトル
	glm::vec3 back_body;


	//要調整！！！
	front_front = _my->m_frontPosition - _you->m_frontPosition;

	back_back = _my->m_backPosition - _you->m_backPosition;

	front_back = _my->m_frontPosition - _you->m_backPosition;

	front_body = _my->m_frontPosition - _you->m_position;

	back_body = _my->m_backPosition - _you->m_position;

	float hitLine = 0.8f;

	if (glm::length(front_front) < hitLine || glm::length(back_back) < hitLine ||
		glm::length(front_back) < hitLine || glm::length(front_body) < hitLine || glm::length(back_body) < hitLine){
		return true;
	}

	return false;

}



//----------------------------------------
//更新と描画

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

	//深度テスト
	glEnable(GL_DEPTH_TEST);

	//ライト
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//毎フレーム
	sprintf_s(str_lapCount, "%d", player->m_lapCount);
	sprintf_s(str_time, "%02d:%02d:%03d", minute, second, milliSecond);

	//コース選択時に1回だけ
	sprintf_s(str_lapMax, "%d", LAP_MAX);

	//-------------------------------------
	//更新

	//レースが始まったらする処理
	camera->update(TYPE_3D);


	if (true == startRace){

		if (false == player->m_isGoal){

			flame++;


			//順位の判定
			for (unsigned int i = 0; i < character.size(); i++){
				std::sort(character.begin(), character.end(), checkRanking);
			}

			//順位の設定
			//実際に順位を付与する処理
			for (unsigned int i = 0; i < character.size(); i++){
				character[i]->m_ranking = i + 1;
			}
		}

		//ミリ秒
		milliSecond = getMilliSecond(flame);

		//秒
		second = getSecond(flame);

		//分
		minute = getMinute(second);
		second = second % 60;

		com1->control();
		com2->control();
		com3->control();


		for (unsigned int i = 0; i < character.size(); i++){

			character[i]->update();

		}

		//接触判定
		for (unsigned int i = 0; i < character.size(); i++){
			for (unsigned int t = i + 1; t < character.size(); t++){

				if (isHitCharacter(character[i], character[t])){

					//1フレーム前の座標に戻して進行方向とは
					//逆のベクトルを足し込む
					character[i]->m_position = character[i]->m_lastPosition;
					glm::vec3 sp = { sin(character[i]->m_rotate.y)*0.01, 0, cos(character[i]->m_rotate.y)*0.01 };
					character[i]->m_speed += sp;
					character[t]->m_speed -= sp;
				}

			}
		}

	}

	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i]->update();
	}

	//-------------------------------------
	//描画(3D)
	course->draw();

	//debug
	for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		course->m_checkPoint[i].draw();
	}

	//for (int i = 0; i < AI_POINT_NUMBER; i++){
	//	course->m_AIPoint[i].draw();
	//}

	glDisable(GL_LIGHTING);

	//車体部と車輪部のみライティングを有効にしてある
	//影部はライティング無効
	for (unsigned int i = 0; i < character.size(); i++){

		character[i]->draw();
		character[i]->drawHasItem();

	}

	//glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i]->draw();
	}

	//ファイアの描画
	/*for (std::vector<FireEffect*>::iterator itr = player->m_useFire.begin(); itr != player->m_useFire.end(); itr++){
		(*itr)->draw();
		}*/


	//ブリザード
	/*glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hoge);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glTranslatef(25, 0.001f, -180);
	glRotatef(90, 1, 0, 0);


	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex2f(-1.f, -1.f);
	glTexCoord2f(0.f, 1.f);
	glVertex2f(-1.f, 1.f);
	glTexCoord2f(1.f, 1.f);
	glVertex2f(1.f, 1.f);
	glTexCoord2f(1.f, 0.f);
	glVertex2f(1.f, -1.f);


	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();*/
	//

	/*更新*/
	camera->update(TYPE_2D);

	countRaceStart();

	/*描画(2D)*/

	//順位の表示
	printRanking();

	printRaceStart();

	//周回カウントの表示
	//文字等の出力を1つの関数にまとめる予定

	if (false == player->m_isGoal){

		//debug
		//if (true == player->m_isGoal){

		StrokeString::print("LAP", { 230, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print(str_lapCount, { 260, 250, 0 }, 0.18f, { 1, 0, 0 });
		StrokeString::print("/", { 275, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print(str_lapMax, { 285, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print("TIME", { 180, 280, 0 }, 0.13f, { 1, 0, 0 });
		StrokeString::print(str_time, { 220, 280, 0 }, 0.13f, { 1, 0, 0 });

		StrokeString::print("LAP1", { 220, 230, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[FIRST], { 250, 230, 0 }, 0.08f, { 1, 0, 0 });

		StrokeString::print("LAP2", { 220, 215, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[SECOND], { 250, 215, 0 }, 0.08f, { 1, 0, 0 });

		StrokeString::print("LAP3", { 220, 200, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[THIRD], { 250, 200, 0 }, 0.08f, { 1, 0, 0 });

	}
	else{

		//GOALの文字
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		{

			glTranslatef(140, 185, 0);

			glBindTexture(GL_TEXTURE_2D, goalTexture);

			glBegin(GL_QUADS);
			{
				glColor4f(1, 1, 1, 1);
				glTexCoord2f(0, 0);
				glVertex2f(0, 0);
				glTexCoord2f(1, 0);
				glVertex2f(150, 0);
				glTexCoord2f(1, 1);
				glVertex2f(150, 80);
				glTexCoord2f(0, 1);
				glVertex2f(0, 80);
			}
			glEnd();
		}
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		StrokeString::print("LAP1", { 60, 158, 0 }, 0.2f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[FIRST], { 130, 158, 0 }, 0.2f, { 1, 0, 0 });

		StrokeString::print("LAP2", { 60, 114, 0 }, 0.2f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[SECOND], { 130, 114, 0 }, 0.2f, { 1, 0, 0 });

		StrokeString::print("LAP3", { 60, 72, 0 }, 0.2f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[THIRD], { 130, 72, 0 }, 0.2f, { 1, 0, 0 });

		StrokeString::print("TOTALTIME", { 24, 30, 0 }, 0.15f, { 1, 0, 0 });
		StrokeString::print(str_time, { 131, 30, 0 }, 0.2f, { 1, 0, 0 });
	}

	glFlush();
}


//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {

	//debug

	for (unsigned int i = 0; i < player->m_hasItem.size(); i++){
		printf("[%d]:", i);

		if (0 == player->m_hasItem[i]){
			printf("ファイア\n");
		}
		else if (1 == player->m_hasItem[i]){
			printf("ブリザガ\n");
		}

	}

	printf("\n");

	//printf("xx:%f yy:%f\n", xx, yy);

	//printf("%d\n", player->m_hasItem.size());

	//printf("player:RANK:%d LAP:%d Now:%d L:%f \n", player->m_ranking, player->m_lapCount, player->m_nowPoint, player->m_nextCheckPointLength);
	//printf("  com1:RANK:%d LAP:%d Now:%d L:%f \n", com1->m_ranking, com1->m_lapCount, com1->m_nowPoint, com1->m_nextCheckPointLength);
	//printf("\n");

	//printf("%f %f\n", xx, yy);

	//printf("%f %f %f\n", player->m_position.x,player->m_position.y, player->m_position.z);
	//printf("%f %f %f\n", com1->m_position.x, com1->m_position.y, com1->m_position.z);
	//printf("%f\n", com1->m_nextCheckPointLength);


	//printf("piyo:%d\n", com1->piyo);

	/*for (int i = 0; i < CHECK_POINT_NUMBER; i++){

		printf("[%d]:%d", i, player->m_passCheckPoint[i]);

		if (CHECK_POINT_NUMBER - 1 == i){
		printf("\n");
		}

		}*/

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);


	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("第4ターム作品審査会");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutJoystickFunc(joystick, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeydown);

	init();//ゲームの初期化

	glutMainLoop();
}