
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include<stdio.h>
#include<stdlib.h>
#include"GameManager.h"
#include"joysticManager.h"
#include"Sound.h"
#include"controller.h"
#include"glut.h"








//-------------------------------------
//fps計測用変数と関数(debug用)

int g_GLframe = 0; //フレーム数
int g_GLtimenow = 0;//経過時間
int g_GLtimebase = 0;//計測開始時間

void fps(){
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	if (g_GLtimenow - g_GLtimebase > 1000)      //１秒以上たったらfpsを出力
	{
		printf("fps:%f\r", g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase));
		g_GLtimebase = g_GLtimenow;//基準時間を設定                
		g_GLframe = 0;//フレーム数をリセット
	}
}


//-------------------------------------
//キーボードからの入力全般

void keyboard(unsigned char key, int x, int y){


}

//----------------------------------------
//更新と描画

void display() {

	GameManager::getInstance()->updata();


}

int flame = 0;

//----------------------------------------
//display関数を60F単位で再帰的に呼び出す関数

void timer(int value) {

	flame++;

	JoysticManager::getInstance()->update();

	//for (int i = 0; i < 4; i++){

	//	if (JoysticManager::getInstance()->m_contoroller[i].m_isConnect){
	//		printf("[%d]:接続されてます", i);
	//	}
	//	else{
	//		printf("[%d]:接続されてません", i);
	//	}

	//	if (i == 3){ printf("\n"); }

	//}

	//printf("%f %f\n", xx, yy);

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);

	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}

int window_width = 900;
int window_height = 900;

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
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}