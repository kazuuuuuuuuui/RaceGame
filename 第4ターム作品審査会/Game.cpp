#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

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
#include"player.h"
#include"Enemy.h"
#include"Item.h"
#include"Effect.h"
#include"Dash.h"
#include"Smoke.h"
#include"moji.h"
#include"joysticManager.h"
#include"Sound.h"
#include"glut.h"

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
		//camera->m_position.x += 10.f;
		xx += 1.f;
	}
	else if ('a' == key){
		//camera->m_position.x -= 10.f;
		xx -= 1.f;
	}
	else if ('w' == key){
		//camera->m_position.y += 10.f;
		yy += 1.f;
	}
	else if ('s' == key){
		//camera->m_position.y -= 10.f;
		yy -= 1.f;
	}
	else if ('r' == key){
		//camera->m_position.z += 10.f;
	}
	else if ('f' == key){
		//camera->m_position.z -= 10.f;
	}


}



//debug
//指定した座標と添え字のチェックポイントまでの距離を返す
//float lengthCheckPoint(glm::vec3 _pos, int _point){
//
//	float length = 0.f;
//	glm::vec3 v;
//
//	v.x = _pos.x - course->m_checkPoint[_point].m_position.x;
//	v.y = _pos.y - course->m_checkPoint[_point].m_position.y;
//	v.z = _pos.z - course->m_checkPoint[_point].m_position.z;
//
//	length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
//
//	return length;
//
//}


//-------------------------------------
//プレイヤーの制御
unsigned int pressedKeys = 0;//現フレーム押されているキー
unsigned int lastkeys = 0;//前フレーム前に押されていたキー
unsigned int changedKeys = 0;//前フレームと現フレームで変化があったキー
unsigned int downkeys = 0;

void joystick(unsigned int buttonMask, int x, int y, int z){

	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	pressedKeys = buttonMask;
	changedKeys = pressedKeys ^ lastkeys;
	downkeys = pressedKeys & changedKeys;

	JoysticManager::getInstance()->m_buttonMask = pressedKeys;
	JoysticManager::getInstance()->m_downKey = downkeys;

	//-1000～1000の値を-1～1の値に変換して渡す
	JoysticManager::getInstance()->m_x = (float)x / 1000.f;
	JoysticManager::getInstance()->m_y = (float)y / 1000.f;
	JoysticManager::getInstance()->m_z = (float)z / 1000.f;

	lastkeys = buttonMask;
}


//----------------------------------------
//更新と描画

void display() {

	GameManager::getInstance()->updata();


}


//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {

	//printf("%f %f\n", xx, yy);

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

	Sound::init();

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutJoystickFunc(joystick, 0);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}