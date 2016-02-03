#pragma once 

#include"Course.h"
#include"GameObject.h"
#include"glut.h"

//アイテム描画
//スフィアマッピング用に
#define ITEM_RADIUS (0.4f)
#define ITEM_SLICE (10)
#define ITEM_STACK (10)
#define ITEM_REPEAT_S (1)
#define ITEM_REPEAT_T (1)

//プレイヤーが所持できる最大アイテム数
#define HAS_ITEM_MAX (3)


//-------------------------------------
//魔石の種類
/*
・ファイア
・ブリザド
*/

enum {
	FIRE = 0,
	BLIZZARD,
	//HASTE,

	ITEM_TYPE_MAX
};



//-------------------------------------
//魔石(アイテム)の情報


class Item : public GameObject{
public:

	//取り敢えず
	int m_flame;

	int m_type;

	//使用されたときにfalseになる
	//デフォルトはtrue
	bool m_isActive;

	//○秒に1回アイテムを再出現させる
	void reCreateItem();

	//プレイヤーにとられたかどうかを判定する
	bool checkIsGotten( glm::vec3 _position);

	//コンストラクタ
	Item() :
		m_flame(0),
		m_type(rand() % ITEM_TYPE_MAX),
		m_isActive(true)

	{};

	void move();
	void draw();
	void update();

};

extern Item *item[SET_ITEM_NUMBER];
extern GLuint ItemFire;
extern GLuint ItemBlizzard;
