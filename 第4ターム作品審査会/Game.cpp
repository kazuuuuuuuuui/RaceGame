/*openGL描画までに必要な初期処理*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"camera.h"
#include"player.h"
#include"Course.h"
#include"MagicStone.h"
#include"glut.h"

Camera *camera = nullptr;

//debug

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
//ゲームの初期化全般を行う

void init(){

	player = new Player();
	camera = new Camera();

	//後で書き換え
	testCourse = new Course();
	testCourse->m_handle = BmpImage::loadImage("bmp/testCourse.bmp");

	magicStone = new MagicStone();

	fire_handle = BmpImage::loadImage("bmp/fire.bmp");
}


//-------------------------------------
//プレイヤーの制御
unsigned int pressedKeys = 0;//現フレーム押されているキー
unsigned int releasedKeys = 0;//現フレーム押されていないキー
unsigned int lastkeys = 0;//前フレーム前に押されていたキー
unsigned int changedKeys = 0;//前フレームと現フレームで変化があったキー

void joystick(unsigned int buttonMask, int x, int y, int z){
	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	pressedKeys = buttonMask;
	releasedKeys = ~pressedKeys;
	changedKeys = pressedKeys ^ lastkeys;

	//-1000～1000の値を-1～1の値に変換して引数として渡す
	player->control(pressedKeys, (float)x / 1000.f, (float)y / 1000.f, (float)z / 1000.f);

	lastkeys = buttonMask;
}


//----------------------------------------
//更新と描画

void display() {
	/*更新*/
	camera->update();
	player->update();






	/*描画*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//深度テスト
	glEnable(GL_DEPTH_TEST);

	testCourse->draw();

	magicStone->draw();

	player->draw();

	glDisable(GL_DEPTH_TEST);

	glFlush();
}


//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {
	system("cls");

	//printf("%d %d %d \n", pix->r, pix->g, pix->b);
	//printf("%f %f", camera->m_position.x, camera->m_position.z);

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

	init();//ゲームの初期化

	glutMainLoop();
}