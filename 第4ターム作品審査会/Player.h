#pragma once

//debug
//デバッグ用に位置いじれるようにしておく
#define PLAYER_TEST_POS_X (20.f)
#define PLAYER_TEST_POS_Y (0.5f)
#define PLAYER_TEST_POS_Z (-160.f)

//プレイヤーが所持出来る魔石の最大数
#define MAGICSTONE_MAX (3)

#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#include<vector>
#include"GameObject.h"
#include"Item.h"
#include"xFile.h"
#include"FireEffect.h"

//-------------------------------------
//自機の情報

class Player :public GameObject{
public:

	//車体部分
	xFile m_boby;

	//後輪部分
	xFile m_backWheel;

	//周回数
	//正規の走法でコースを1周したら+1する
	int m_lapCount;

	//順位
	int m_ranking;

	//既定の周回数に達したらtrueになる
	bool m_isGoal;

	bool m_passCheckPoint[CHECK_POINT_NUMBER];
	//bool m_checkFlag;

	//ラップタイム
	int m_flame;
	int m_milliSecond[LAP_MAX];
	int m_second[LAP_MAX];
	int m_minute[LAP_MAX];
	char m_str_lapTime[LAP_MAX][256];

	//所持している魔石情報
	//魔石を示すポインタのベクター
	std::vector<Item*> m_hasMagicStone;

	//ファイアを使ったときのエフェクトを管理
	std::vector<FireEffect*> m_useFire;

	void draw();
	void update();
	void control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z);

	void checkCourseOut();

	bool inDart();

	//周回系
	bool countLap();
	bool checkIsGoal();

	//アイテム系
	int hasMagicStoneNumber();



	//後で書き換える
	Player() :
		m_flame(0),
		m_lapCount(1),
		m_ranking(1),
		m_isGoal(false)

	{
		//debug
		m_position.x = PLAYER_TEST_POS_X;
		m_position.y = PLAYER_TEST_POS_Y;
		m_position.z = PLAYER_TEST_POS_Z;

		m_scale.x = 0.18f;
		m_scale.y = 0.18f;
		m_scale.z = 0.18f;

		//ラップタイムの初期化
		for (int i = 0; i < LAP_MAX; i++){
			m_milliSecond[i] = 0;
			m_second[i] = 0;
			m_minute[i] = 0;
		}

	}

};

extern Player *player;