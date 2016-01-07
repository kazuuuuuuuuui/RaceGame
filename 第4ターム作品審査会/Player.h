#pragma once

#include"FlyingObject.h"

//-------------------------------------
//自機の情報

class Player :public FlyingObject{
public:

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);
	bool inDart();

	//後で書き換える
	Player(){
		m_position.x = 22.f;
		m_position.y = 0.01f;
		m_position.z = -68.f;
	}

};

extern Player *player;