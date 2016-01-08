#pragma once

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

	MagicStone m_magicStone[MAGICSTONE_MAX];

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);
	bool inDart();
	bool getMagicStone();

	//後で書き換える
	Player(){
		m_position.x = 22.f;
		m_position.y = 0.5f;
		m_position.z = -68.f;

		/*m_scale.x = 0.1f;
		m_scale.y = 0.1f;
		m_scale.z = 0.1f;*/
	}

};

extern Player *player;