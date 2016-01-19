/*openGL描画までに必要な初期処理*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include"GameManager.h"
#include"camera.h"
#include"player.h"
#include"Enemy.h"
#include"Course.h"
#include"CourseFlag.h"
#include"MagicStone.h"
#include"StrokeString.h"
#include"FireEffect.h"
#include"glut.h"

/***********debug***********/

#define COURSE_TYPE (1)


Enemy *com1 = nullptr;

/**************************/




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

	if (' ' == key){
		glm::vec3 accelIncrement(-0.015*sin(player->m_rotate.y), 0, -0.015*cos(player->m_rotate.y));
		player->m_accel = accelIncrement;
	}
	else{
		player->m_accel = { 0.f, 0.f, 0.f };
	}

}


void specialkeydown(int key, int x, int y){

	if (GLUT_KEY_LEFT == key){
		player->m_rotate.y += 0.02f;
	}

	if (GLUT_KEY_RIGHT == key){
		player->m_rotate.y -= 0.02f;
	}

}

GLuint hoge = 0;

//取り敢えず
Course* createCourse(){

	Course *course = nullptr;
	course = new Course();



	//コースによって異なる部分
	//コース1(仮)
	//debug
	if (1 == COURSE_TYPE){
		//チェックポイントの位置設定
		course->m_checkPoint[0].m_position = { 22.5f, 0.01f, -195.f };
		course->m_checkPoint[1].m_position = { 75.f, 0.01f, -230.f };
		course->m_checkPoint[2].m_position = { 170.f, 0.01f, -180.f };
		course->m_checkPoint[3].m_position = { 241.f, 0.01f, -170.f };
		course->m_checkPoint[4].m_position = { 130.f, 0.01f, -115.f };
		course->m_checkPoint[5].m_position = { 175.f, 0.01f, -75.f };
		course->m_checkPoint[6].m_position = { 230.f, 0.01f, -15.f };
		course->m_checkPoint[7].m_position = { 150.f, 0.01f, -35.f };
		course->m_checkPoint[8].m_position = { 47.f, 0.01f, -25.f };
		course->m_checkPoint[9].m_position = { 24.f, 0.01f, -115.f };

		course->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1/course1.bmp");
		//course->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/course1/background1.bmp");
		BmpImage::makeBuffer("bmp/course1/buffer1.bmp", course->m_buffer);
	}
	//

	//コース2(仮)
	else if (2 == COURSE_TYPE){
		course->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course2/course2.bmp");
		//course->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/course2/background2.bmp");
		BmpImage::makeBuffer("bmp/course2/buffer2.bmp", course->m_buffer);
	}
	//

	course->setMagicStone();

	return course;

}



//-------------------------------------
//ゲームの初期化全般を行う

void init(){

	srand(time(NULL));

	//ゲームマネージャーの生成
	gameManager = new GameManager();

	//プレイヤーの生成
	player = new Player();
	xFile::loadXfile("xFile/testbike.x", player->m_boby);
	xFile::loadXfile("xFile/taiya.x", player->m_backWheel);

	//敵の生成
	com1 = new Enemy();
	com1->m_position = { 20, 0.5f, -160 };
	com1->m_accel = { 0.001*sin(com1->m_rotate.y), 0, 0.001*cos(com1->m_rotate.y) };
	xFile::loadXfile("xFile/testbike.x", com1->m_boby);
	xFile::loadXfile("xFile/taiya.x", com1->m_backWheel);

	//カメラの生成
	camera = new Camera();

	//アイテム生成→コースの生成→アイテムの設置

	//アイテムの生成
	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i] = new MagicStone();
	}

	//後で書き換え
	//コースの生成
	gameManager->m_course = createCourse();

	//テクスチャの読み込み
	//透過度無し
	//testCourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1/course1.bmp");
	//testCourse->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/course1/background1.bmp");

	//透過度有り
	smoke_handle = BmpImage::loadImage_alpha("bmp/Effect/smoke.bmp");

	hoge = BmpImage::loadImage_alpha("bmp/Effect/blizzard.bmp");

	//使用する魔石のテクスチャ読み込み
	fire_handle = BmpImage::loadImage("bmp/MagicStone/ms_fire.bmp");
	blizzard_handle = BmpImage::loadImage("bmp/MagicStone/ms_blizzard.bmp");


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

	//-1000～1000の値を-1～1の値に変換して引数として渡す
	player->control(pressedKeys, downkeys, (float)x / 1000.f, (float)y / 1000.f, (float)z / 1000.f);

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
	sprintf(str_lapCount, "%d", player->m_lapCount);
	sprintf(str_time, "%02d:%02d:%03d", minute, second, milliSecond);

	//コース選択時に1回だけ
	sprintf(str_lapMax, "%d", LAP_MAX);

	/*更新*/
	flame++;

	//ミリ秒
	milliSecond = getMilliSecond(flame);

	//秒
	second = getSecond(flame);

	//分
	minute = getMinute(second);

	second = second % 60;


	camera->update(TYPE_3D);
	gameManager->m_course->update();
	player->update();
	com1->update();
	com1->AI();

	//testCourse->update();

	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i]->update();
	}

	//ファイアの更新
	for (std::vector<FireEffect*>::iterator itr = player->m_useFire.begin(); itr != player->m_useFire.end(); itr++){
		(*itr)->update();
	}

	/*描画(3D)*/
	gameManager->m_course->draw();
	//testCourse->draw();

	//debug
	/*for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		testCourse->m_checkPoint[i].draw();
		}*/

	for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		gameManager->m_course->m_checkPoint[i].draw();
	}

	player->draw();

	com1->draw();

	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);


	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i]->draw();
	}

	//ファイアの描画
	for (std::vector<FireEffect*>::iterator itr = player->m_useFire.begin(); itr != player->m_useFire.end(); itr++){
		(*itr)->draw();
	}


	//ブリザード
	glPushMatrix();

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


	glPopMatrix();
	//

	/*更新*/
	camera->update(TYPE_2D);



	/*描画(2D)*/

	//周回カウントの表示
	//文字等の出力を1つの関数にまとめる予定

	if (false == player->m_isGoal){
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
		StrokeString::print("GOAL", { 75, 210, 0 }, 0.5f, { 1, 1, 1 });
	}

	glFlush();
}


//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {

	//debug
	/*for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		printf("[%d]:%d", i, player->m_passCheckPoint[i]);

		if (9 == i){
			printf("\n");
		}

	}*/

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);


	//fps();

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