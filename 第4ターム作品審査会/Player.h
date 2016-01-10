#pragma once

//ゴールに必要なコースの周回数
#define LAP_MAX (3)

//プレイヤーが所持出来る魔石の最大数
#define MAGICSTONE_MAX (3)

//プレイヤーが所持している魔石の1つ目
#define MAGICSTONE_FIRST (0)

//プレイヤーが所持している魔石の2つ目
#define MAGICSTONE_SECOND (1)

//プレイヤーが所持している魔石の3つ目
#define MAGICSTONE_THIRD (2)

#include<vector>
#include"FlyingObject.h"
#include"MagicStone.h"
#include"xFile.h"

//-------------------------------------
//自機の情報

class Player :public FlyingObject{
public:

	//頂点数
	unsigned int m_vertices;

	//インデックス数
	unsigned int m_indeces;

	//頂点情報
	std::vector<float>m_vertex;

	//インデックス情報
	std::vector<unsigned short>m_index;

	//法線情報
	std::vector<float>m_normal;

	//周回数
	//正規の走法でコースを1周したら+1する
	int m_lapCount;

	//チェックポイントを順走するとtrueになる
	//m_lapCountが+1された際にすべてのフラグをfalseに戻す
	bool m_checkFlag;

	MagicStone m_magicStone[MAGICSTONE_MAX];

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);
	bool inDart();

	bool getMagicStone();

	bool passCheckPoint();
	bool countLap();
	bool isGoal();

	//後で書き換える
	Player() :
		m_lapCount(0),
		m_checkFlag(false)
	{
		m_position.x = 45.f;
		m_position.y = 0.5f;
		m_position.z = -150.f;

		/*m_scale.x = 0.15f;
		m_scale.y = 0.15f;
		m_scale.z = 0.15f;*/
	}

};

extern Player *player;