#pragma once 

#include"Course.h"
#include"FlyingObject.h"
#include"glut.h"

//コースに配置されている魔石の数
#define SET_MAGICSTONE_NUMBER (20)

//-------------------------------------
//魔石の種類
/*
・ファイア
・ブリザド
・サンダー

・ヘイスト
・ミニマム
・アルテマ


*/

enum {
	FIRE = 0,
	BLIZZARD,
	//HASTE,

	MAGIC_TYPE_MAX
};



//-------------------------------------
//魔石(アイテム)の情報


class MagicStone : public FlyingObject{
public:

	int m_type;

	//プレイヤーによって取得されているかのフラグ
	//デフォルトはfalse
	bool m_isGotten;

	//使用されたときにfalseになる
	//デフォルトはtrue
	bool m_isActive;

	//プレイヤーにとられたかどうかを判定する
	bool checkIsGotten();

	//コンストラクタ
	MagicStone() :
		m_type(rand() % MAGIC_TYPE_MAX),
		m_isGotten(false),
		m_isActive(true)

	{};

	void draw();
	void update();

};

extern MagicStone *magicStone[SET_MAGICSTONE_NUMBER];
extern GLuint fire_handle;
extern GLuint blizzard_handle;
extern GLuint haste_handle;