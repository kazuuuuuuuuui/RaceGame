#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<algorithm>
#include<list>
#include"GameManager.h"
#include"camera.h"
#include"Item.h"
#include"Effect.h"
#include"Dash.h"
#include"Smoke.h"
#include"moji.h"
#include"joysticManager.h"
#include"Sound.h"
#include"controller.h"
#include"glut.h"

int window_width = 900;
int window_height = 900;

//debug
float xx = 0.f;
float yy = 0.f;

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

//-------------------------------------
//プレイヤーの制御
//unsigned int pressedKeys = 0;//現フレーム押されているキー
//unsigned int lastkeys = 0;//前フレーム前に押されていたキー
//unsigned int changedKeys = 0;//前フレームと現フレームで変化があったキー
//unsigned int downkeys = 0;

void joystick(unsigned int buttonMask, int x, int y, int z){

	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	//pressedKeys = buttonMask;
	//changedKeys = pressedKeys ^ lastkeys;
	//downkeys = pressedKeys & changedKeys;

	//JoysticManager::getInstance()->m_buttonMask = pressedKeys;
	//JoysticManager::getInstance()->m_downKey = downkeys;

	////-1000～1000の値を-1～1の値に変換して渡す
	//JoysticManager::getInstance()->m_x = (float)x / 1000.f;
	//JoysticManager::getInstance()->m_y = (float)y / 1000.f;
	//JoysticManager::getInstance()->m_z = (float)z / 1000.f;

	//lastkeys = buttonMask;
}


//----------------------------------------
//更新と描画

void display() {

	GameManager::getInstance()->updata();


}


//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {

	JoysticManager::getInstance()->update();

	//printf("%f %f\n", xx, yy);

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);

	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}


//-------------------------------------
//画面の比率が変わった時に描画サイズを再計算するコールバック関数

void reshape(int width, int height)
{
	window_width = width;
	window_height = height;

}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("第4ターム作品審査会");

	Sound::init();

	JoysticManager::getInstance();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutJoystickFunc(joystick, 0);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}