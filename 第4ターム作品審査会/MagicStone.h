#pragma once 

#include"Course.h"
#include"FlyingObject.h"
#include"glut.h"

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
	Blizzard,
	Thunder,

	MAGIC_TYPE_MAX
};



//-------------------------------------
//魔石(アイテム)の情報


class MagicStone : public FlyingObject{
public:

	int m_type;
	bool m_isActive;

	//コンストラクタ
	MagicStone() :
		m_type(FIRE),
		m_isActive(false)

		//後で書き換え
	{
		m_position.x = 20.f;
		m_position.y = 0.5;
		m_position.z = -190.f;
	};

	void draw();

};

extern MagicStone *magicStone;
extern GLuint fire_handle;
extern GLuint blizzard_handle;