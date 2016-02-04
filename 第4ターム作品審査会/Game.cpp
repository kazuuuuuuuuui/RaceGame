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
#include"Course.h"
#include"CourseFlag.h"
#include"Item.h"
#include"Effect.h"
#include"Fire.h"
#include"Blizzard.h"
#include"Dash.h"
#include"Smoke.h"
#include"WavFile.h"
#include"moji.h"
#include"joysticManager.h"
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
//ゲームの初期化全般を行う

//後で書き換え
xFile body;
xFile backWheel;


void init(){

	srand(time(NULL));


	pushAnykey = new Moji(150.f, 40.f, { 70, 37 }, { 1, 1, 1 }, "bmp/title/pushAnyKey.bmp");



	//アイテム生成→コースの生成→アイテムの設置
	//アイテムの生成
	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i] = new Item();
	}

	//モデルデータの読み込み
	xFile::loadXfile("xFile/testbike.x", body);
	xFile::loadXfile("xFile/taiya.x", backWheel);

	//車体のモデルデータの向き修正
	body.rotate();

	//後で書き換え
	//プレイヤーの生成
	player = new Player();
	player->m_type = PLAYER0;
	player->m_body = body;
	player->m_backWheel = backWheel;

	//敵の生成
	com1 = new Enemy();
	com1->m_type = PLAYER1;
	com1->m_body = body;
	com1->m_backWheel = backWheel;

	//
	com2 = new Enemy();
	com2->m_type = PLAYER2;
	com2->m_body = body;
	com2->m_backWheel = backWheel;

	//
	com3 = new Enemy();
	com3->m_type = PLAYER3;
	com3->m_body = body;
	com3->m_backWheel = backWheel;

	//生成したプレイヤーと敵をベクターで管理
	character.push_back(player);
	character.push_back(com1);
	character.push_back(com2);
	character.push_back(com3);

	//カメラの生成
	camera = new Camera();

	//テクスチャの読み込み
	//透過度無し

	titleTexture = BmpImage::loadImage("bmp/title/title.bmp");
	courseSelectBG = BmpImage::loadImage("bmp/courseSelect/courseSelectBG.bmp");

	threeTexture = BmpImage::loadImage_alpha("bmp/start/three.bmp");
	twoTexture = BmpImage::loadImage_alpha("bmp/start/two.bmp");
	oneTexture = BmpImage::loadImage_alpha("bmp/start/one.bmp");
	goTexture = BmpImage::loadImage_alpha("bmp/start/go.bmp");
	goalTexture = BmpImage::loadImage_alpha("bmp/goal.bmp");

	smoke_handle = BmpImage::loadImage_alpha("bmp/Effect/smoke.bmp");
	dash_handle = BmpImage::loadImage_alpha("bmp/Effect/dash.bmp");

	rank1st = BmpImage::loadImage_alpha("bmp/Ranking/1st.bmp");
	rank2nd = BmpImage::loadImage_alpha("bmp/Ranking/2nd.bmp");
	rank3rd = BmpImage::loadImage_alpha("bmp/Ranking/3rd.bmp");
	rank4th = BmpImage::loadImage_alpha("bmp/Ranking/4th.bmp");

	dashIcon = BmpImage::loadImage_alpha("bmp/dashIcon.bmp");
	dashGauge = BmpImage::loadImage_alpha("bmp/gauge.bmp");

	EffectBlizzard = BmpImage::loadImage_alpha("bmp/Effect/blizzard.bmp");

	//使用する魔石のテクスチャ読み込み
	ItemFire = BmpImage::loadImage("bmp/MagicStone/ms_fire.bmp");
	ItemBlizzard = BmpImage::loadImage("bmp/MagicStone/ms_blizzard.bmp");

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

	init();//ゲームの初期化

	glutMainLoop();
}